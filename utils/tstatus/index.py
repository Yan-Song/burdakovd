#!/usr/bin/python
# -*- coding: utf8 -*-

from google.appengine.api import urlfetch
from google.appengine.api import memcache
import re
import time
import logging

class config:
  static_url = '/static'
  debug = True

class problem:
    tries = 0
    c = 0
    def __init__(self, pid, name, source, percent, solvers):
        self.pid = pid
        self.name = name
        self.source = source
        self.percent = percent
        self.solvers = solvers
    def __repr__(self):
        return (u"<problem instance: {name: %s, source: %s, percent: %s, solvers: %s}>" % \
            (repr(self.name), repr(self.source), self.percent, self.solvers)).encode("utf-8")
    def complexity(self, lastnum):
        """will be used by sort
        чем меньше людей задачу решили, тем она сложнее
        а также учитываем, что на решение старых задач было больше времени"""
        self.c = 1000000 * (lastnum + 200 - self.pid) / (self.solvers + 3)

def fetch(url, cachetime):
    """Качает страницу по http, возможно некоторое кэширование результатов в datastore"""
    
    key = "urlfetch: " + url
    page = memcache.get(key)
    
    if page == None:
        logging.info("fetching %s ..." % url)
        
        response = urlfetch.fetch(url)
        if response.status_code == 200:
            page = response.content
            logging.info("... fetched %d bytes from %s" % (len(page), url))
            # сохранить в кэш
            memcache.set(key, page, cachetime)
        else:
            throw (url, response.status_code)
    
    return page.decode("utf-8")

def fetchproblems():
    """качает список всех задач с тимуса"""
    problems = []
    re_problems = re.compile(r'\<TR\>\<TD\>\<BR\>\</TD\>\<TD\>(\d{4})\</TD\>\<TD\ CLASS\=\"na' + \
        'me\"\><A[^\>]+\>([^\<]+)\<\/A\>\<\/TD\><TD\ CLASS\=\"source\">([^\<]*)</TD>\<TD\><A[^\>]' + \
        '+\>([^\<]+)\<\/A\>\<\/TD\>\<TD\><A[^\>]+\>([^\<]+)\<\/A\>\<\/TD\>\<\/TR\>', re.IGNORECASE)

    # кэшируем список задач на сутки
    html = fetch("http://acm.timus.ru/problemset.aspx?space=1&page=all&locale=ru", 86400)
    cp = re_problems.findall(html)
    if config.debug:
        logging.debug("parsed %d problems" % len(cp))
    for pid, name, source, percent, solved in cp:
        problems.append(problem(int(pid), name, source, percent, int(solved)))
    return problems

def format(problem, tries):
    return (u"""<TR><TD>%s</TD><TD>%d</TD>
        <TD CLASS="name"><A HREF="http://acm.timus.ru/problem.aspx?space=1&amp;num=%d">%s</A></TD>
        <TD CLASS="source">%s</TD>
        <TD><A HREF="http://acm.timus.ru/detail.aspx?space=1&amp;num=%d">%s</A></TD>
        <TD><A HREF="http://acm.timus.ru/rating.aspx?space=1&amp;num=%d">%s</A></TD>
        </TR>""" %
        (
        ("""<img src="%s/ok.gif">""" % config.static_url) if problem.solved else (u"""\n<img src="%s/failed.png" alt="попытка">""" % config.static_url)*tries, problem.pid, \
        problem.pid, problem.name, problem.source, problem.pid, \
        problem.percent, problem.pid, problem.solvers))

def form():
    return """<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
        <html><head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Нерешённые задачи</title>
        </head>
        <body alink="#1a5cc8" link="#1a5cc8" vlink="#1a5cc8">
        <p>Зайдите на Тимусе в инфо о себе, посмотрите свой системный id (НЕ JUDGE_ID), и введите его в форму</p>
        <p><img src="%s/scr.png" alt="скриншот">
        

        <p>
        <FORM ACTION="." METHOD="GET" STYLE="margin-top:0.6em;">
        <INPUT NAME="uid" SIZE="15" VALUE="62871"> <INPUT TYPE="SUBMIT" VALUE="го"></FORM>
       
        </body></html>
        """ % config.static_url;

def main(uid, showsolved = True):
    uid = int(uid) # на всякий случай, чтоб исключить любой инклудинг
    problems = fetchproblems()
    lastnum = max([problem.pid for problem in problems])
    map(lambda x: x.complexity(lastnum), problems)
    problems.sort(lambda x, y: x.c-y.c)
    c = [problem.c for problem in problems]
    minc = min(c)
    maxc = max(c)
    # качаем инфу о авторе, кэшируем на пять минут
    html = fetch("http://acm.timus.ru/author.aspx?id=%d&locale=ru" % uid, 300)
    name = re.findall(ur'\<FONT\ SIZE\=\"5\"\>([^\<]+)\<\/FONT\>', html, re.IGNORECASE)[0]
    place = int(re.findall(
        ur'\<TD\ CLASS\=\"name\"\>Место\<\/TD\>\<TD\ CLASS\=\"value\"\>(\d+)\<\/TD\>', \
        html, re.IGNORECASE)[0])
    p = re.findall(ur'\<NOBR\>\<A[^\>]+\>(\d{4})\<\/A\>\ \<FONT\ SIZE\=\"\-2\"\>(\d+)\/(\d+)\<\/FONT\>\,?\<\/NOBR\>', \
        html, re.IGNORECASE)
    solvedproblems = set()
    trieslist = {}
    for num, solved, tries in p:
        trieslist[int(num)] = int(tries)
        if int(solved) > 0: solvedproblems.add(int(num))
    total = len(problems)
    for p in problems:
        p.solved = p.pid in solvedproblems
    if not showsolved:
        problems = filter(lambda x: not(x.solved), problems)
    header = u"""<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
        <html><head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <style type="text/css">
        <!--
        %s
        -->
        </style>
        <title>Нерешённые задачи: %s</title>
        </head><body alink="#1a5cc8" link="#1a5cc8" vlink="#1a5cc8">
        <p><a href="http://acm.timus.ru/author.aspx?id=%d">%s</a>, решено %d из %d задач, место: %d.</p>
        <p align="center">
        <TABLE WIDTH="80%%" CLASS="problemset strict">
        <TR><TH WIDTH="40">Неудачные попытки</TH><TH WIDTH="50">ID</TH>
        <TH>Название</TH><TH>Источник</TH><TH WIDTH="100">Зачтено</TH>
        <TH WIDTH="100">Авторы</TH>
        <TH WIDTH="40">Сложность</TH></TR>

        """ % (

        u"""
                    CODE, TT, PRE
            {
                    font-family: monospace, "monospace for firefox";
                    font-size: 0.81em;
            }
            SUP
            {
                    vertical-align: baseline;
                    position: relative;
                    top: -0.4em;
            }
            SUB
            {
                    vertical-align: baseline;
                    position: relative;
                    bottom: -0.4em;
            }
            PRE.intable
            {
                    margin: 0;
            }

            TABLE.strict A, TABLE.strict A:hover, TABLE.strict A:visited
            {
                    color: #000000;
            }
            DIV#help_text CODE
            {
                    font-size: 0.81em;
            }
            DIV#help_text PRE.code
            {
                    background-color: #F0F0F0;
                    padding: 4px;
            }
            H1.title, H2.title
            {
                    color: #1A5CC8;
                    text-align: center;
            }
            H2.subtitle, H3.subtitle
            {
                    color: #1A5CC8;
                    text-align: left;
            }

            /********** status **********/

            TABLE.status
            {
                    margin: 0px;
                    padding: 0px;
                    border-top: 1px solid #808080;
                    border-bottom: 1px solid #808080;
                    font: 14px Arial, Helvetica, sans-serif;
                    color: #000000;
                    text-align: center;
                    background-color: #FFFFFF;
                    width: 100%;
            }

            TABLE.status TR.header
            {
                    height: 36px;
                    font-weight: bold;
                    font-size: 13px;
                    background-color: #EEEEEE;
            }
            TABLE.status TR.even
            {
                    height: 37px;
            }
            TABLE.status TR.odd
            {
                    height: 37px;
                    background-color: #F4F4F4;
            }

            TABLE.status TD, TABLE.status TH
            {
                    padding: 2px 6px;
            }
            TABLE.status TD
            {
                    border-top: 1px solid #DDDDDD;
            }
            TABLE.status .id
            {
                    width: 64px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .date
            {
                    width: 86px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .coder
            {
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status TD.coder
            {
                    text-align: left;
            }
            TABLE.status .problem
            {
                    width: 68px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .language
            {
                    width: 76px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .result, TABLE.status .verdict_wt, TABLE.status .verdict_ac, TABLE.status .verdict_rj
            {
                    width: 160px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .verdict_ac
            {
                    color: #006600;
            }
            TABLE.status .verdict_rj, TABLE.status .verdict_rj A, TABLE.status .verdict_rj A:hover, TABLE.status .verdict_rj A:visited
            {
                    color: #800000;
            }
            TABLE.status .test
            {
                    width: 52px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .runtime
            {
                    width: 68px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.status .memory
            {
                    width: 76px;
            }

            TABLE.status_footer
            {
                    margin: 10px 0px 0px 0px;
                    font: 14px Arial, Helvetica, sans-serif;
                    color: #000000;
                    text-align: left;
                    width: 100%;
            }
            TABLE.status_footer TD.footer_left
            {
                    padding: 0px 32px 0px 0px;
            }
            TABLE.status_footer TD.footer_right
            {
                    text-align: right;
                    vertical-align: top;
            }

            P.status_filter
            {
                    margin: 0px;
                    padding: 0px 0px 4px 0px;
                    border: 0px;
                    font: 12px Arial, Helvetica, sans-serif;
                    color: #000000;
                    text-align: right;
            }

            TABLE.status A, TABLE.status_footer A, P.status_filter A
            {
                    color: #0044CC;
                    text-decoration: underline;
            }

            /********** rating **********/

            TABLE.rating
            {
                    margin-bottom: 10px;
                    padding: 0px;
                    border-top: 1px solid #808080;
                    font: 14px Arial, Helvetica, sans-serif;
                    color: #000000;
                    text-align: center;
                    background-color: #FFFFFF;
            }

            TABLE.rating TR.header
            {
                    height: 36px;
                    font-weight: bold;
                    font-size: 13px;
                    background-color: #EEEEEE;
            }
            TABLE.rating TR.even, TABLE.rating TR.odd
            {
                    height: 37px;
            }
            TABLE.rating TR.odd
            {
                    background-color: #F4F4F4;
            }

            TABLE.rating TH, TABLE.rating TD
            {
                    padding: 2px 6px;
                    border-right: 1px solid #DDDDDD;
            }
            TABLE.rating TD
            {
                    border-top: 1px solid #DDDDDD;
            }

            TABLE.rating .rank
            {
                    border-left: 1px solid #DDDDDD;
                    width: 52px;
            }
            TABLE.rating .id
            {
                    width: 64px;
            }
            TABLE.rating .date
            {
                    width: 86px;
            }
            TABLE.rating .coder
            {
                    width: 248px;
            }
            TABLE.rating TD.coder
            {
                    text-align: left;
            }
            TABLE.rating .language
            {
                    width: 76px;
            }
            TABLE.rating .runtime
            {
                    width: 68px;
            }
            TABLE.rating .memory
            {
                    width: 76px;
            }
            TABLE.rating TD.footer
            {
                    padding: 10px 0px 0px 0px;
                    border-top: 1px solid #808080;
                    border-right: none;
            }

            TABLE.rating_footer
            {
                    font: 14px Arial, Helvetica, sans-serif;
                    color: #000000;
                    width: 100%;
            }
            TABLE.rating_footer TD
            {
                    padding: 0px;
                    border: none;
                    vertical-align: top;
            }
            TABLE.rating_footer TD.footer_left
            {
                    padding-right: 32px;
                    text-align: left;
            }
            TABLE.rating_footer TD.footer_right
            {
                    text-align: right;
            }

            TABLE.rating A
            {
                    color: #0044CC;
                    text-decoration: underline;
            }

            /********** problem **********/

            TABLE.sample
            {
                    border-collapse: collapse;
                    border: solid 1px #1A5CC8;
            }
            TABLE.sample TR TD, TABLE.sample TR TH
            {
                    border: solid 1px #1A5CC8;
                    vertical-align: top;
                    padding: 3px;
            }
            TABLE.sample TR TH
            {
                    color: #1A5CC8;
            }

            H2.problem_title
            {
                    text-align: center;
                    font-weight: normal;
                    font-size: 2em;
                    color: #1A5CC8;
                    margin: 0;
            }
            H3.problem_subtitle
            {
                    color: #1A5CC8;
                    margin: 14px 0 4px 0;
            }
            DIV.problem_limits
            {
                    text-align: center;
                    margin: 0 0 14px 0;
                    line-height: 1.4em;
            }
            DIV.problem_source
            {
                    margin: 10px 0 0 0;
                    line-height: 1.4em;
            }
            DIV.problem_links
            {
                    font-size: 1.15em;
                    margin: 14px 0 0 0;
            }

            DIV.problem_centered_picture
            {
                    text-align: center;
                    margin: 12px 0 12px 0;
            }
            IMG.problem_laimage
            {
                    margin: 4px 15px 6px 0;
            }
            IMG.problem_raimage
            {
                    margin: 4px 0 6px 15px;
            }

            DIV.problem_par, DIV.problem_par_pre
            {
                    margin: 0 0 10px 0;
            }
            DIV.problem_par
            {
                    line-height: 1.4em;
            }
            DIV.problem_par_normal
            {
                    text-align: justify;
            }
            DIV.problem_par_center
            {
                    text-align: center;
            }
            DIV.problem_par_right
            {
                    text-align: right;
                    font-style: italic;
                    padding-left: 60px;
            }

            DIV.problem_par UL, DIV.problem_par OL
            {
                    margin-top: 4px;
                    margin-bottom: 10px;
            }
            DIV.problem_par TABLE
            {
                    border: solid 1px Black;
                    border-collapse: collapse;
            }
            DIV.problem_par TABLE TR TH, DIV.problem_par TABLE TR TD
            {
                    border: solid 1px Black;
                    padding: 4px;
            }
            DIV.problem_par TABLE PRE
            {
                    margin: 0;
            }

            /********** problemset **********/

            TABLE.problemset
            {
                    border: solid 1px #999;
                    border-collapse: collapse;
            }
            TABLE.problemset TR TH, TABLE.problemset TR TD
            {
                    border: solid 1px #999;
                    padding: 3px;
            }
            TABLE.problemset TR TH
            {
                    color: Black;
                    background-color: #A4C6FF;
                    text-align: center;
            }
            TABLE.problemset TR TD
            {
                    color: Black;
                    background-color: #C6C6C6;
                    text-align: center;
            }
            TABLE.problemset TR TD.name
            {
                    text-align: left;
            }

            /********** ranklist **********/

            TABLE.ranklist
            {
                    border: solid 1px #999;
                    border-collapse: collapse;
            }
            TABLE.ranklist TR TH, TABLE.ranklist TR TD
            {
                    border: solid 1px #999;
                    padding: 2px 4px;
            }
            TABLE.ranklist TR TH
            {
                    color: Black;
                    background-color: #A4C6FF;
                    text-align: center;
            }
            TABLE.ranklist TR TD
            {
                    color: Black;
                    background-color: #C6C6C6;
                    text-align: center;
            }
            TABLE.ranklist TR TD.name
            {
                    text-align: left;
            }
            TABLE.ranklist TR TD.first
            {
                    font: bold 1.3em Arial, Helvetica, sans-serif;
            }
            TABLE.ranklist TR TD.current
            {
                    background-color: #D4D4D4;
            }

            /********** monitor **********/

            TABLE.monitor
            {
                    border: solid 1px #BBB;
                    border-collapse: collapse;
            }
            TABLE.monitor TR TD
            {
                    border: solid 1px #BBB;
                    padding: 1px 4px;
                    text-align: center;
            }
            TABLE.monitor TR TD.author
            {
                    text-align: left;
            }
            TABLE.monitor TR TD .time
            {
                    font-size: 0.63em;
            }
            TABLE.monitor TR TD.acc
            {
                    color: #070;
            }
            TABLE.monitor TR TD.rej
            {
                    color: #B00;
            }

            /********** stats **********/

            TABLE.stats
            {
                    border-width: 0px;
                    border-collapse: collapse;
            }
            TABLE.stats TR TD
            {
                    padding: 2px;
                    vertical-align: middle;
            }
            TABLE.stats TR TD.name
            {
                    width: 200px;
                    text-align: left;
                    font: 1.13em Arial, Helvetica, sans-serif;
            }
            TABLE.stats TR TD.value
            {
                    width: 70px;
                    text-align: right;
                    font: 1.19em monospace, "monospace for firefox";
            }

            /********** news **********/

            DIV.news_block
            {
                    margin: 1.2em 0em 1.2em 0em;
            }
            DIV.news_caption
            {
                    font-weight: bold;
                    font-size: 1.19em;
                    margin-bottom: 0.3em;
                    border-bottom: dashed 1px Silver;
            }
            img
            {
                    //padding: 2px;
                    //margin: 0px;
            }
            """
            , name, uid, name, len(solvedproblems), total, place)
    footer = u"""</TABLE></body></html>"""
    return (header + u'\n'.join(
            map(
                lambda i: format(problems[i], trieslist.get(problems[i].pid, 0)),
                range(len(problems))
               )
           ) + footer).encode("utf-8")

def index(uid = -1):
    if uid == -1: return form()
    else: return main(uid)

if __name__ == '__main__': print main(62871) # for testing
