#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
R3C — GitHub Discussions 자동 문서화 (v7.0)
- GraphQL API 사용
- 페이지네이션 + 레이트리밋 재시도
- 최근 N일 필터링, 최대 N개 수집
- 마크다운 요약(Top, Category별, Raw Table)
"""

import os, sys, time, datetime, requests
from datetime import timezone, timedelta

OWNER = os.getenv("REPO_OWNER", "0200134")
REPO  = os.getenv("REPO_NAME", "r3c")
OUT   = os.getenv("OUTPUT_PATH", "docs/community_feedback.md")
LIMIT = int(os.getenv("DISCUSSION_LIMIT", "100"))
DAYS  = int(os.getenv("DAYS_WINDOW", "180"))
TOKEN = os.getenv("GITHUB_TOKEN")

if not TOKEN:
    print("❌ GITHUB_TOKEN is missing", file=sys.stderr); sys.exit(1)

API = "https://api.github.com/graphql"
HEADERS = {"Authorization": f"bearer {TOKEN}"}
KST = timezone(timedelta(hours=9))
NOW_KST = datetime.datetime.now(KST)

QUERY = """
query($owner:String!, $name:String!, $pageSize:Int!, $after:String) {
  repository(owner: $owner, name: $name) {
    discussions(first: $pageSize, after: $after, orderBy: {field: UPDATED_AT, direction: DESC}) {
      pageInfo { hasNextPage endCursor }
      nodes {
        number
        title
        url
        createdAt
        updatedAt
        author { login }
        category { name }
        comments { totalCount }
        bodyText
      }
    }
  }
}
"""

def run_query(variables, retries=4):
    for i in range(retries):
        r = requests.post(API, json={"query": QUERY, "variables": variables}, headers=HEADERS, timeout=30)
        if r.status_code == 200:
            j = r.json()
            if "errors" in j:
                # 레이트리밋/간헐 오류 재시도
                if i < retries - 1:
                    time.sleep(2 * (i + 1)); continue
                print(f"GraphQL errors: {j['errors']}", file=sys.stderr)
                sys.exit(1)
            return j
        time.sleep(2 * (i + 1))
    print(f"HTTP error: {r.status_code} {r.text}", file=sys.stderr)
    sys.exit(1)

def fetch_discussions(limit):
    items, after = [], None
    page_size = min(50, max(1, limit))
    while len(items) < limit:
        data = run_query({"owner": OWNER, "name": REPO, "pageSize": page_size, "after": after})
        repo = data.get("data", {}).get("repository")
        if not repo: break
        d = repo["discussions"]
        items.extend(d.get("nodes") or [])
        if not d["pageInfo"]["hasNextPage"] or not d["pageInfo"]["endCursor"]: break
        after = d["pageInfo"]["endCursor"]
    return items[:limit]

def within_days(ts_iso, days):
    dt = datetime.datetime.fromisoformat(ts_iso.replace("Z", "+00:00"))
    return (NOW_KST - dt.astimezone(KST)) <= datetime.timedelta(days=days)

def md_escape(s: str) -> str:
    return (s or "").replace("|", "\\|").replace("\r", "").strip()

def build_markdown(discussions):
    # 최근 DAYS 내 업데이트만
    recent = [d for d in discussions if within_days(d["updatedAt"], DAYS)]
    # 카테고리 그룹화
    by_cat = {}
    for d in recent:
        cat = (d.get("category") or {}).get("name") or "Uncategorized"
        by_cat.setdefault(cat, []).append(d)

    lines = []
    lines.append("# 🗣️ R3C Community Feedback Log")
    lines.append("")
    lines.append(f"> Last updated: {NOW_KST.strftime('%Y-%m-%d %H:%M KST')}  \n"
                 f"> Window: last **{DAYS}** days, collected **{len(recent)}** items (max {LIMIT})")
    lines.append("\n---\n")

    if not recent:
        lines.append("_No discussions found in the selected window._\n")
        return "\n".join(lines)

    # Top (업데이트순 상위 10)
    lines.append("## 🔝 Top Updated")
    for d in recent[:10]:
        lines.append(f"- **[{md_escape(d['title'])}]({d['url']})** "
                     f"(#{d['number']}, by @{(d.get('author') or {}).get('login','unknown')}; "
                     f"{d['comments']['totalCount']} comments; "
                     f"updated {d['updatedAt'][:10]})")
    lines.append("")

    # Category별
    lines.append("## 🗂️ By Category")
    for cat in sorted(by_cat.keys(), key=str.lower):
        lines.append(f"### {md_escape(cat)}")
        for d in by_cat[cat][:20]:
            lines.append(f"- [{md_escape(d['title'])}]({d['url']}) "
                         f"(#{d['number']}, {d['comments']['totalCount']} comments, "
                         f"updated {d['updatedAt'][:10]})")
        lines.append("")

    # Raw table
    lines.append("## 📜 Raw List (Updated DESC)\n")
    lines.append("| # | Title | Comments | Updated | Link |")
    lines.append("|---:|-------|---------:|---------|------|")
    for d in recent:
        lines.append(f"| {d['number']} | {md_escape(d['title'])} | "
                     f"{d['comments']['totalCount']} | {d['updatedAt'][:10]} | "
                     f"[open]({d['url']}) |")
    lines.append("")

    # (선택) 본문 미니 요약
    lines.append("## 📝 Snippets (first 2,000 chars)")
    for d in recent[:8]:
        body = (d.get("bodyText") or "").strip().replace("\r", "")
        short = (body[:2000] + "...") if len(body) > 2000 else (body or "_No content._")
        lines.append(f"### {md_escape(d['title'])}\n{short}\n")

    return "\n".join(lines)

def main():
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    items = fetch_discussions(LIMIT)
    md = build_markdown(items)
    with open(OUT, "w", encoding="utf-8") as f:
        f.write(md)
    print(f"✅ Wrote digest → {OUT} (items fetched: {len(items)})")

if __name__ == "__main__":
    main()
