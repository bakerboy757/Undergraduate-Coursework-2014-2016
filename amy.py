import praw
import time
import re
import sqlite3 as lite
import sys
import data

con = lite.connect('amy_stats.db')
with con:
    print "Creating table if not exists"
    cur = con.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS meta (id INTEGER PRIMARY KEY, sub TEXT, date TEXT, user TEXT, product_id TEXT);")

bot = praw.Reddit(user_agent=data.user_agent,
                client_id=data.client_id,
                client_secret=data.client_secret,
                username=data.username,
                password=data.password)

amazon_expression = 'http[s]://www.amazon.com/.*/dp[^).\n ]*'
bad_amazon_expression = '\]\(http[s]://www.amazon.com/.*/dp[^).\n ]*'
subreddit = bot.subreddit('all')
comments = subreddit.stream.comments()

for comment in comments:
    text = comment.body
    author = comment.author
    if comment.subreddit in data.banned_subs:
        continue
    if re.search(bad_amazon_expression, text) is None and re.search(amazon_expression, text) is not None and author != 'AMY_bot' and author != 'le_velocirapetor':
        print "\n\nFOUND: {0}".format(author)
        link = re.search(amazon_expression, text)
        if link is None:
            continue
        dp = re.search('http[s]://www.amazon.com/.*/dp/(.*)/[^).\n ]*', link.group(0))
        if dp is None:
            continue
        with con:
            print "adding comment data"
            cur = con.cursor()
            cur.execute("INSERT INTO meta(sub, date, user, pid) VALUES (?, ?, ?, ?)", (comment.subreddit, time.strftime("%c"), author, dp.group(1)))
            print "successfully inserted"
        message = "For less messy amazon links you can extract the part after \"/dp/\" in \n\n {0}\n\nand make it:\n\nhttps://amzn.com/{1}\n\n Or via [smile](http://smile.amazon.com/gp/chpf/about/ref=smi_aas_redirect?ie=UTF8&*Version*=1&*entries*=0) link:\n\n https://smile.amazon.com/dp/{2}\n\n**BEEP BOP**\n\nPlz send any recommendations via PM".format(link.group(0), dp.group(1), dp.group(1))
        comment.reply(message)
