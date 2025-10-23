#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
R3C — GitHub Discussions 자동 문서화 스크립트 (GraphQL API 버전)
매주 1회 실행되어 최신 Discussion 내용을 docs/community_feedback.md 로 기록합니다.
"""

import os
import requests
import datetime

# ==========================================================
# ⚙️ 환경 설정
# ==========================================================
REPO_OWNER = "0200134"
REPO_NAME = "r3c"
OUTPUT_PATH = "docs/community_feedback.md"
TOKEN = os.getenv("GITHUB_TOKEN")

GRAPHQL_URL = "https://api.github.com/graphql"
HEADERS = {"Authorization": f"bearer {TOKEN}"}

if not TOKEN:
    print("❌ Error: GITHUB_TOKEN environment variable not set.")
    exit(1)

# ==========================================================
# 📡 GraphQL Query
# ==========================================================
QUERY = """
query($owner:String!, $name:String!, $count:Int!) {
  repository(owner: $owner, name: $name) {
    discussions(first: $count, orderBy: {field: UPDATED_AT, direction: DESC}) {
      nodes {
        title
        url
        createdAt
        updatedAt
        author { login }
        bodyText
        comments { totalCount }
      }
    }
  }
}
"""

# ==========================================================
# 🧩 Discussions Fetcher
# ==========================================================
def fetch_discussions(limit=20):
    """Fetch discussions from GitHub GraphQL API"""
    variables = {"owner": REPO_OWNER, "name": REPO_NAME, "count": limit}
    res = requests.post(GRAPHQL_URL, json={"query": QUERY, "variables": variables}, headers=HEADERS)
    if res.status_code != 200:
        print(f"⚠️ API Error: {res.status_code} {res.text}")
        return []
    data = res.json().get("data", {}).get("repository", {}).get("discussions", {}).get("nodes", [])
    return data or []

# ==========================================================
# 🧾 Markdown Writer
# ==========================================================
def write_to_markdown(discussions):
    """Write discussion data into docs/community_feedback.md"""
    os.makedirs(os.path.dirname(OUTPUT_PATH), exist_ok=True)
    now = datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S UTC")

    with open(OUTPUT_PATH, "w", encoding="utf-8") as f:
        f.write("# 🗣️ R3C Community Feedback Log\n\n")
        f.write(f"> Last updated: {now}\n\n")
        f.write("---\n\n")

        if not discussions:
            f.write("_No discussions found._\n")
            return

        for d in discussions:
            title = d.get("title", "Untitled")
            url = d.get("url", "")
            author = (d.get("author") or {}).get("login", "unknown")
            created = d.get("createdAt", "unknown")[:10]
            updated = d.get("updatedAt", "unknown")[:10]
            comments = d.get("comments", {}).get("totalCount", 0)
            body = d.get("bodyText", "").strip().replace("\r", "")
            short_body = (body[:2000] + "...") if len(body) > 2000 else body

            f.write(f"## [{title}]({url})\n")
            f.write(f"**Author:** @{author} | **Created:** {created} | **Updated:** {updated} | **Comments:** {comments}\n\n")
            f.write(short_body or "_No content._")
            f.write("\n\n---\n\n")

    print(f"✅ {len(discussions)} discussions documented → {OUTPUT_PATH}")

# ==========================================================
# 🚀 Entry Point
# ==========================================================
def main():
    discussions = fetch_discussions(limit=30)
    if not discussions:
        print("⚠️ No discussions returned from API.")
        return
    write_to_markdown(discussions)

if __name__ == "__main__":
    main()
