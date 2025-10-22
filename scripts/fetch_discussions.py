#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
R3C — GitHub Discussions 자동 문서화 스크립트
주 1회 실행되어 최신 Discussion 내용을 docs/community_feedback.md 로 기록합니다.
"""

import requests, os, datetime

REPO = "0200134/r3c"
TOKEN = os.getenv("GITHUB_TOKEN")
OUTPUT = "docs/community_feedback.md"

def fetch_discussions():
    headers = {"Authorization": f"token {TOKEN}"}
    url = f"https://api.github.com/repos/{REPO}/discussions?per_page=100"
    resp = requests.get(url, headers=headers)
    if resp.status_code != 200:
        print(f"⚠️ API Error: {resp.status_code}")
        return []
    return resp.json()

def write_to_markdown(data):
    os.makedirs("docs", exist_ok=True)
    now = datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S UTC")
    with open(OUTPUT, "w", encoding="utf-8") as f:
        f.write(f"# 🗣️ R3C Community Feedback Log\n\n")
        f.write(f"> Last updated: {now}\n\n---\n")
        for d in data:
            title = d.get("title", "Untitled")
            author = d.get("user", {}).get("login", "unknown")
            created = d.get("created_at", "unknown")
            body = d.get("body", "")
            f.write(f"## {title}\n")
            f.write(f"**Author:** {author} | **Created:** {created}\n\n")
            f.write(body[:2000])  # 본문 너무 길면 일부만 기록
            f.write("\n\n---\n")

def main():
    discussions = fetch_discussions()
    if not discussions:
        print("No discussions found.")
        return
    write_to_markdown(discussions)
    print(f"✅ {len(discussions)} discussions documented to {OUTPUT}")

if __name__ == "__main__":
    main()
