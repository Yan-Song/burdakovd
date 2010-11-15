#!/usr/bin/python
# -*- coding: utf8 -*-

import sys, os
sys.path.append(".")
from BeanCounterDB import data, constant_count
import BeanCounterDB

import time


# some html helpers

htmldir = "html"
dbversions = ["3"]
transactionsperpage = 500
topprofitlimit = 5000
onmainpagecountlimit = 1000

def timing(name):
    def impl(f):
        def timed(*args, **kwargs):
            start = time.time()
            result = f(*args, **kwargs)
            finish = time.time()
            print "ran %s, elapsed %.3f seconds" % (name, finish - start)
            return result
        return timed
    return impl

def doNothing(f):
    def q(*args, **kwargs):
        pass
    return q

def prn(s):
    if type(s) is unicode: print s.encode("cp866")
    else: print s.decode("utf-8").encode("cp866")

def write(fn, title, body):
    if type(title)==type(u""): title = title.encode("utf8")
    if type(body)==type(u""): body = body.encode("utf8")
    fname = os.path.join(htmldir, fn+".html")
    prn (u"Создаю %s" % fname)
    f = file(fname, "w")
    text = u"""<html>
    <head>

    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>%s</title>
    
    <link rel="stylesheet" href="../static/style.css" type="text/css"/>
    
    <!-- flot -->
    <script src="../static/jquery-1.3.2.min.js" language="javascript" type="text/javascript"></script>
    <script src="../static/flot/jquery.flot.pack.js" language="javascript" type="text/javascript"></script>
    <!--[if IE]>
    <script language="javascript" type="text/javascript" src="../static/flot/excanvas.pack.js"></script>
    <![endif]-->
    <!-- /flot -->
    
    <!-- WoWHead MouseOver-Tooltip -->
    <script src="http://ru.wowhead.com/widgets/power.js" type="text/javascript"></script>
    <!-- /WoWHead MouseOver-Tooltip -->

    <script language="javascript" type="text/javascript" src="../static/main.js"></script>
    
    </head>
    <body>
    <div id="layout">
    <div id="main">
    <div class="path">
    <a href="index.html">На главную</a>
    </div>
    
    <div id="main-contents" class="main-contents">
    %s
    </div>
    </div>
    </div>
    <div id="footer"><small>Burdakov Daniel, 2010</small></div>
    </body>
    </html>""".encode("utf8") % (title, body)
    f.write(text)
    f.close()

def ul(t, cls="default"):
    return "<ul class='%s'>%s</ul>" % (cls, "\n".join(map(lambda x: "<li>%s</li>" % x, t)))

def img(u):
    return """<img src="%s"/>""" % u

def link(href, text, cls="default"):
    return "<a class='%s' href='%s'>%s</a>" % (cls, href, text)

def p(text, cls="p"):
    return "<div class='%s'>%s</div>" % (cls, text)

def div(text, cls="default", ID=None):
    if ID: return "<div class='%s' id='%s'>%s</div>" % (cls, ID, text)
    else: return "<div class='%s'>%s</div>" % (cls, text)

def span(text, cls="default"):
    return "<span class='%s'>%s</span>" % (cls, text)

def table(text, cls="listview-mode-default", pager=""):
    return """<div class="listview">%s<table class='%s'>%s</table>%s</div>""" % \
        (div(pager, "listview-band-top"), cls, text, div(pager, "listview-band-bottom"))

def thead(text, cls="default"):
    return "<thead class='%s'>%s</thead>" % (cls, text)

def tbody(text, cls="default"):
    return "<tbody class='%s'>%s</tbody>" % (cls, text)

def tr(text, cls="default"):
    return "<tr class='%s'>%s</tr>" % (cls, text)

def th(text, cls="default"):
    return "<th class='%s'><div><a><span>%s</span></a></div></th>" % (cls, text)

def td(text, cls="default"):
    return "<td class='%s'>%s</td>" % (cls, text)

def small(text, cls="default"):
    return "<small class='%s'>%s</small>" % (cls, text)

def h(text, cls="headline"):
    return "<h3 class='%s'>%s</h3>" % (cls, text)

def faction(f, text=None):
    if text is None: text = f
    if f == "Alliance": return span(text, "alliance-icon")
    if f == "Horde": return span(text, "horde-icon")
    return span(text, "unknown-faction")
        
def gold(amount):
    if amount<0:
        amount = -amount
        sign = "-"
    else:
        sign = ""
    amount = int(amount)
    g = amount/10000
    s = amount/100%100
    c = amount % 100
    if g>0:
        return """<span class="moneygold">%s%d</span><span class="moneysilver">%d</span><span class="moneycopper">%d</span>""" % (sign, g, s, c)
    elif s>0:
        return """<span class="moneysilver">%s%d</span><span class="moneycopper">%d</span>""" % (sign, s, c)
    else: return """<span class="moneycopper">%s%d</span>""" % (sign, c)

def itemlink(ids):
    item = BeanCounterDB.names.get(ids, "cffff1010;??")
    color, name = item.split(";")
    itemid = ids.split(":")[0]
    color = color[3:]
    return """<a class='itemlink' href="http://ru.wowhead.com/?item=%s" style="color: #%s">%s</a>""" % \
        (itemid, color, name)

def itemname(ids):
    item = BeanCounterDB.names.get(ids, "cffff1010;??")
    color, name = item.split(";")
    return name

#########

realms = data.keys()

def get_ids(string):
    s = string.split(":")
    s = s[1] + ":" + s[7]
    return s

class transaction:
    time = None
    def __init__(self, category, itemstring, line):
        self.category = category
        self.ids = get_ids(itemstring)
        self.itemstring = itemstring
        self.line = line
        #print line
        #print category
        if category=="completedAuctions":
            self.stack, self.money, self.deposit, self.fee, self.buyout, \
            self.bid, self.buyer, self.time, self.reason, self.location = \
                line.split(";")
            if self.deposit=="": self.deposit = 0
            self.stack = int(self.stack)
        elif category=="completedBidsBuyouts":
            self.stack, self.money, self.deposit, self.fee, self.buyout, \
            self.bid, self.seller, self.time, self.reason, location = \
                line.split(";")
            if self.deposit=="": self.deposit = 0
            self.stack = int(self.stack)
        elif category=="failedAuctions":
            self.stack, self.money, self.deposit, self.fee, self.buyout, \
            self.bid, self.seller, self.time, self.reason, location = line.split(";")
            self.stack = int(self.stack)
            if self.deposit=="": self.deposit = 0
        else: raise ValueError()
        self.time = int(self.time)
    def tr(self, realm, faction):
        import time
        date = time.strftime("%d.%m.%Y %H:%M:%S", time.localtime(self.time))
        item = itemlink(self.ids) + " " + \
            link("%s-%s-%s.html" % (realm, faction, htmlize(self.ids)), img("../static/stat.png"), "more")
        #item += small(link("%s-%s-%s.html" % , "статистика"))
        if self.category=="completedAuctions":
            action = div(u"Продано", "sold")
            stack = int(self.stack)
            if not self.fee: fee = 0
            else: fee = int(self.fee)
            if self.money: price = int(self.money) - int(self.deposit) + fee
            else: price = 0
            pprice = gold(price / stack)
            price = gold(price)
            if not self.money:
                price = "???"
                pprice = "???"
            buyer_seller = self.buyer
            if self.fee: fee_depo = gold(fee)
            else: fee_depo = "???"
        elif self.category=="completedBidsBuyouts":
            stack = int(self.stack)
            if self.bid!=self.buyout:
                action = div(u"Выиграно", "bought")
                price = int(self.bid)
            else:
                action = div(u"Куплено", "bought")
                if self.buyout: price = int(self.buyout)
                else: price = 0
            pprice = gold(price / stack)
            price = gold(price)
            if not self.buyout:
                price = "???"
                pprice = "???"
            buyer_seller = self.seller
            fee_depo = ""
            action = div(action) + small(self.reason)
        elif self.category=="failedAuctions":
            action = div(u"Не продано", "failed")
            stack = int(self.stack)
            price = int(self.buyout)
            pprice = gold(price/stack)
            price = gold(price)
            buyer_seller = ""
            fee_depo = gold(int(self.deposit))
        else: raise ValueError()
        return tr(td(date)+td(action)+td(item)+td(stack)+td(price)+\
            td(pprice)+td(fee_depo)+td(small(buyer_seller)))
    def profit(self):
        if self.category=="completedAuctions":
            if self.money: money = int(self.money)
            return money - int(self.deposit)
        elif self.category=="completedBidsBuyouts":
            if self.bid!=self.buyout:
                return -int(self.bid)
            else:
                if self.buyout: return -int(self.buyout)
                else: return 0
        elif self.category=="failedAuctions":
            return -int(self.deposit)
        else: raise ValueError();

@timing("getrows")
def getrows(c):
    return \
        sum( # суммируем по категориям
            map(
                lambda category:
                    sum( # суммируем по itemid
                        map(
                            lambda itemidset:
                                sum( # суммируем по itemstring
                                    map(
                                        lambda itemstring:
                                            map(
                                                lambda info:
                                                    transaction(category, itemstring, info),
                                                itemidset[itemstring].values()
                                            ),
                                        itemidset.keys()
                                    ),
                                []),
                            c[category].values()
                        ),
                        []
                    ),
                ("completedAuctions", "failedAuctions", "completedBidsBuyouts")
            ),
            []
        )

def sizeof(t):
  if type(t)==type(""): return len(t)
  if type(t)==type(u""): return len(t)
  if type(t)==type([]):
      ans=0
      for k in t:
          ans = ans + sizeof(k)
      return ans
  if type(t)==type({}):
   ans=0
   for k,v in t.items():
    ans = ans + sizeof(k) + sizeof(v)
   return ans
  return 200

lasts = []
markets = {}
realchars = {}

def mktable(log, url, title, preambule, realm, faction):
    pages = max((len(log) + transactionsperpage - 1) / transactionsperpage, 1)
    for i in range(pages):
        pager = span(u"Страница %d из %d" % (i+1, pages))
        if i>0: pager = link("%s-%d.html" % (url, i), u"< Позже") + pager
        if i>0: pager = link("%s-%d.html" % (url, 1), u"<< Самые новые") + pager
        if i<pages-1: pager += link("%s-%d.html" % (url, i+2), u"Раньше >")
        if i<pages-1: pager += link("%s-%d.html" % (url, pages), u"Самые старые >>")
        pager = div(pager, "listview-nav")
        s = preambule.encode("utf8") + \
            table(
                thead(tr(th(u"Дата")+th(u"Действие")+th(u"Предмет")+\
                th(u"Стек")+th(u"Стоимость")+th(u"За штуку")+\
                th(u"fee/deposit")+th(u"Игрок"))).encode("utf8")
                + "\n".join(map(lambda op: op.tr(realm, faction).encode("utf-8"), \
                log[i*transactionsperpage:(i+1)*transactionsperpage]))
                , pager=pager.encode("utf-8"))
        write("%s-%d" % (url, i+1), title, p(s))

def profit(seq):
    return sum(map(lambda z: z.profit(), seq))

def check_category(seq, cat):
    return sum(map(lambda z: z.profit(), filter(lambda z: z.category==cat, seq)))

def lostbuy(seq):
    return -check_category(seq, "completedBidsBuyouts")

def lostdepo(seq):
    return -check_category(seq, "failedAuctions")

def gainedsells(seq):
    return check_category(seq, "completedAuctions")

def htmlize(ids):
    return ids.replace(":", "-")

def group_days(market, f):
    json = {}
    for (ids, log) in market.items():
        for t in log:
            year, month, day, hour, _, _, _, _, _ = time.localtime(t.time)
            hour = 12
            tm = time.mktime((year, month, day, hour, 0, 0, 0, 0, 0))
            if json.has_key(tm):
                json[tm] = list(map(lambda (x,y): x+y, zip(json[tm], f(t))))
            else:
                json[tm] = list(f(t))
    js = map(list, json.items())
    js.sort(key=lambda x: x[0])
    jss = []
    for [k, v] in js:
        if jss:
            if k-jss[-1][0]>24*3600:
                jss.append(None)
        jss.append([k, v])
    return repr(list(jss)).replace("None", "null")

def group_weeks(market, f):
    json = {}
    for (ids, log) in market.items():
        for t in log:
            year, month, day, hour, _, _, wday, _, _ = time.localtime(t.time)
            hour = 12
            tm = time.mktime((year, month, day, hour, 0, 0, 0, 0, 0)) - wday*24*3600
            if json.has_key(tm):
                json[tm] = list(map(lambda (x,y): x+y, zip(json[tm], f(t))))
            else:
                json[tm] = list(f(t))
    js = map(list, json.items())
    js.sort(key=lambda x: x[0])
    jss = []
    for [k, v] in js:
        if jss:
            if k-jss[-1][0]>7*24*3600:
                jss.append(None)
        jss.append([k, v])
    return repr(list(jss)).replace("None", "null")

def group_months(market, f):
    json = {}
    for (ids, log) in market.items():
        for t in log:
            year, month, day, _, _, _, _, _, _ = time.localtime(t.time)
            day = 1
            tm = time.mktime((year, month, day, 0, 0, 0, 0, 0, 0))
            if json.has_key(tm):
                json[tm] = list(map(lambda (x,y): x+y, zip(json[tm], f(t))))
            else:
                json[tm] = list(f(t))
    js = map(list, json.items())
    js.sort(key=lambda x: x[0])
    jss = []
    for [k, v] in js:
        if jss:
            if k-jss[-1][0]>32*24*3600:
                jss.append(None)
        jss.append([k, v])
    return repr(list(jss)).replace("None", "null")


@timing("main")
def main():

    for realm in realms:
        chars = data[realm].keys()
        prn( realm + ": " + ", ".join(chars))
        for char in chars:
            # check db version
            cversion = BeanCounterDB.settings[realm][char]["version"]
            if not(cversion in dbversions):
                write(char+"-data", u"История торговли %s" % char, \
                    p(u"""База, полученная от BeanCounter для %s имеет версию "%s", а этот
                    скрипт умеет работать только с базами версии %s.""" % \
                    (char, cversion, ", ".join(map(str, dbversions)))))
                continue
            
            # general
            c = data[realm][char]
            f = BeanCounterDB.settings[realm][char]["faction"]
            
            # raw data
            log = getrows(c)

            # process it
            if log:
                log.sort(key=lambda x: -x.time)
                
                realchars.setdefault(realm, [])
                realchars[realm].append((char, f))
                
                lasts.append(max(map(lambda transaction: int(transaction.time), log)))
                
                mktable(log, "%s-%s-data" % (realm, char), \
                    u"История торговли %s" % char, h(u"%s, %s" % (faction(f, char), \
                    gold(BeanCounterDB.settings[realm][char]["wealth"]))) + \
                    div(u"""%s потратил на покупки %s, на депозиты %s, получил с продаж %s""" % \
                        (
                        char,
                        gold(lostbuy(log)),
                        gold(lostdepo(log)),
                        gold(gainedsells(log)),
                        ), "text"),
                    realm, f
                )

                # gathering statistics
                markets.setdefault(realm, {})
                markets[realm].setdefault(f, {})
                for t in log:
                    markets[realm][f].setdefault(t.ids, [])
                    markets[realm][f][t.ids].append(t)

        # do market (not character) specific processing
        for fac in markets.get(realm, {}).keys():
            mname = "%s-%s" % (realm, fac)
            prn( mname)
            market = markets[realm][fac]
            # for flot
            tf = lambda t: \
                (
                    #0.0001*t.profit(),
                    0.0001*check_category([t], "completedAuctions"), # сумма продаж

                    0.0001*(-check_category([t], "completedBidsBuyouts") \
                    -check_category([t], "failedAuctions")), # сумма покупок и фэйлов

                    1 if t.category=="completedAuctions" else 0, # кол-во продаж
                    
                    1 if t.category=="completedBidsBuyouts" else 0, # кол-во покупок

                    1, # кол-во всех транзакций

                    0.0001*t.profit(), # общая прибыль
                )
            jsw = group_weeks(market, tf)
            jsm = group_months(market, tf)
            
            preambule = h("%s - %s" % (realm, fac)) + \
            div(u"""На этом сервере мы торгуем %d видами товаров,
            на текущий момент прибыль на аукционе составляет %s<br/>
            Всего потрачено на покупки %s, на депозиты %s, получено с продаж %s""" % \
            (len(market),
                gold(sum(map(lambda i: profit(i), market.values()))),
                gold(sum(map(lambda i: lostbuy(i), market.values()))),
                gold(sum(map(lambda i: lostdepo(i), market.values()))),
                gold(sum(map(lambda i: gainedsells(i), market.values()))),
                ), "text") + \
                u"<table><thead><tr><th>По неделям</th><th>По месяцам</th></tr></thead><tbody>" + \
                tr(
                    td(div(div("", "graph", "placeholderglobalw1"), "gwrapper")) + \
                    td(div(div("", "graph", "placeholderglobalm1"), "gwrapper"))
                ) + \
                tr(
                    td(div(div("", "graph", "placeholderglobalw3"), "gwrapper")) + \
                    td(div(div("", "graph", "placeholderglobalm3"), "gwrapper"))
                ) + \
                tr(
                    td(div(div("", "graph", "placeholderglobalw"), "gwrapper")) + \
                    td(div(div("", "graph", "placeholderglobalm"), "gwrapper"))
                ) + \
                tr(
                    td(div(div("", "graph", "placeholderglobalw2"), "gwrapper")) + \
                    td(div(div("", "graph", "placeholderglobalm2"), "gwrapper"))
                ) + "</tbody></table>"
            
            script = u"""
                <script type="text/javascript">
                //<![CDATA[
                gdata.globalw = %s;
                gdata.globalm = %s;
                $(
                function()
                {
                    xx = {
                        mode: "time",
                        //timeformat: "%%d.%%m.%%y",
                    };
                    yy =  {
                        tickFormatter: goldformatter,
                    };
                    
                    drawGraph("#placeholderglobalw", [ [0,{label: "Получено с продаж", color: "rgb(0, 200, 0)"}],
                    [1,{label: "Затрачено на покупки и депозиты", color: "rgb(255, 100, 100)"}] ], gdata.globalw,
                    {xaxis: xx, yaxis: yy, lines: {show: true}, points: {show: true}});
                    
                    drawGraph("#placeholderglobalm", [ [0,{label: "Получено с продаж", color: "rgb(0, 200, 0)"}],
                    [1,{label: "Затрачено на покупки и депозиты", color: "rgb(255, 100, 100)"}] ], gdata.globalm,
                    {xaxis: xx, yaxis: yy, lines: {show: true}, points: {show: true}});


                    drawGraph("#placeholderglobalw1", [ [5,{label: "Прибыль", color: "rgb(0, 200, 0)"}]
                    ], gdata.globalw,
                    {xaxis: xx, yaxis: yy, lines: {show: true}, points: {show: true}});
                    
                    drawGraph("#placeholderglobalm1", [ [5,{label: "Прибыль", color: "rgb(0, 200, 0)"}],
                     ], gdata.globalm,
                    {xaxis: xx, yaxis: yy, lines: {show: true}, points: {show: true}});


                    drawGraph("#placeholderglobalw2", [ [2,{label: "Количество продаж", color: "rgb(0, 200, 0)"}],
                    [3,{label: "Количество покупок", color: "rgb(255, 100, 100)"}] ], gdata.globalw,
                    {xaxis: xx, lines: {show: true}, points: {show: true}});
                    
                    drawGraph("#placeholderglobalm2", [ [2,{label: "Количество продаж", color: "rgb(0, 200, 0)"}],
                    [3,{label: "Количество покупок", color: "rgb(255, 100, 100)"}] ], gdata.globalm,
                    {xaxis: xx, lines: {show: true}, points: {show: true}});


                    drawGraph("#placeholderglobalw3", [ [4,{label: "Активность", color: "rgb(0, 200, 0)"}]
                    ], gdata.globalw,
                    {xaxis: xx, lines: {show: true}, points: {show: true}});
                    
                    drawGraph("#placeholderglobalm3", [ [4,{label: "Активность", color: "rgb(0, 200, 0)"}],
                     ], gdata.globalm,
                    {xaxis: xx, lines: {show: true}, points: {show: true}});


                }
                );
                //]]>
                </script>

                """ % (jsw, jsm)

            head = thead(tr(th(u"Предмет")+th(u"Затрачено на покупку")+\
                th(u"Затрачено на депозиты")+th(u"Получено с продаж")+th(u"Прибыль")))
            
            sorts = map(lambda (item, log): (item, -lostbuy(log)-gainedsells(log)), market.items())
            sorts.sort(key=lambda q: q[1])
            sorts = sorts[:topprofitlimit]
            ssorts = sorts[:onmainpagecountlimit]

            body = tbody(
            "\n".join(
                    map(
                        lambda (ids, gained):
                            tr(
                            td(
                                itemlink(ids) + " " + \
                                    link("%s-%s.html" % (mname, htmlize(ids)), img("../static/stat.png"), "more")
                            ) +
                            td(
                                gold(lostbuy(market[ids]))
                            ) +
                            td(
                                gold(lostdepo(market[ids]))
                            ) +
                            td(
                                gold(gainedsells(market[ids]))
                            ) +
                            td(
                                gold(profit(market[ids]))
                            )
                            ),
                        ssorts
                    )
                )
            )

            s = preambule + script + table(head + body)
            write(mname, "%s - %s" % (realm, fac), s)
            #print market
            for (ids, _) in sorts:
                # item specific pages
                iname = "%s-%s" % (mname, htmlize(ids))
                imarket = {ids: market[ids]}
                #print imarket

                soldcount = sum(map(lambda z: z.stack, \
                    filter(lambda z: z.category=="completedAuctions", market[ids])))
                gsells = gainedsells(market[ids])
                boughtcount = sum(map(lambda z: z.stack, \
                    filter(lambda z: z.category=="completedBidsBuyouts", market[ids])))
                lbuy = lostbuy(market[ids])
                failedcount = sum(map(lambda z: z.stack, \
                    filter(lambda z: z.category=="failedAuctions", market[ids])))
                tried = soldcount + failedcount
                
                preambule = h("%s - %s: %s" % (realm, fac, itemlink(ids))) + \
                div(
                u"""Всего куплено %s таких предметов (в среднем по %s),
                продано %s (в среднем по %s)<br/>
                Шанс продажи: %s%% (%d из %d)
                """ %
                (boughtcount,
                gold(lbuy/boughtcount) if boughtcount else "??",
                soldcount, gold(gsells/soldcount) if soldcount else "??",
                int(100.0*soldcount/tried) if tried else "??",
                soldcount, tried, ),
                "text")

                head = thead(th(u"По неделям")+th(u"По месяцам"))
                body = tbody(
                    tr(
                        td(div(div("", "graph", "placeholder1w"), "gwrapper")) + \
                        td(div(div("", "graph", "placeholder1m"), "gwrapper"))
                    )
                    + \
                    tr(
                        td(div(div("", "graph", "placeholder2w"), "gwrapper")) + \
                        td(div(div("", "graph", "placeholder2m"), "gwrapper"))
                    )
                    + \
                    tr(
                        td(div(div("", "graph", "placeholder3w"), "gwrapper")) + \
                        td(div(div("", "graph", "placeholder3m"), "gwrapper"))
                    )
                    + \
                    tr(
                        td(div(div("", "graph", "placeholder4w"), "gwrapper")) + \
                        td(div(div("", "graph", "placeholder4m"), "gwrapper"))
                    )
                )

                tf = lambda z: \
                    (
                        int(z.stack) if z.category=="completedAuctions" else 0,
                        int(z.stack) if z.category=="completedBidsBuyouts" else 0,
                        0.0001*z.profit() if z.category=="completedAuctions" else 0,
                        -0.0001*z.profit() if z.category=="completedBidsBuyouts" else 0,
                        int(z.stack) if z.category=="failedAuctions" else 0,
                        0.0001*z.profit()
                    )
                
                jsw = group_weeks(imarket, tf)
                jsm = group_months(imarket, tf)
                
                script = u"""
                    <script type="text/javascript">
                    //<![CDATA[
                    gdata.gw = itemhelper(%s);
                    gdata.gm = itemhelper(%s);
                    $(
                    function()
                    {
                        yg =  {
                            tickFormatter: goldformatter,
                            min: 0,
                        };

                        ygs =  {
                            tickFormatter: goldformatter,
                        };

                        yy = {
                            min: 0,
                        };

                        ychance = {
                            min: 0,
                            max: 100,
                            tickFormatter: pformatter,
                        };
                        
                        xtime = {
                            mode: "time",
                        };
                        
                        drawGraph("#placeholder1w", [ [0,{label: "Объём продаж", color: "rgb(0, 200, 0)"}],
                        [1,{label: "Объём закупок", color: "rgb(255, 100, 100)"}] ], gdata.gw,
                        {xaxis: xtime, yaxis: yy, lines: {show: true}, points: {show: true}});
                        
                        drawGraph("#placeholder1m", [ [0,{label: "Объём продаж", color: "rgb(0, 200, 0)"}],
                        [1,{label: "Объём закупок", color: "rgb(255, 100, 100)"}] ], gdata.gm,
                        {xaxis: xtime, yaxis: yy, lines: {show: true}, points: {show: true}});


                        drawGraph("#placeholder2w", [ [6,{label: "Цена продаж", color: "rgb(0, 200, 0)"}],
                        [7,{label: "Цена закупок", color: "rgb(255, 100, 100)"}] ], gdata.gw,
                        {xaxis: xtime, yaxis: yg, lines: {show: true}, points: {show: true}});
                        
                        drawGraph("#placeholder2m", [ [6,{label: "Цена продаж", color: "rgb(0, 200, 0)"}],
                        [7,{label: "Цена закупок", color: "rgb(255, 100, 100)"}] ], gdata.gm,
                        {xaxis: xtime, yaxis: yg, lines: {show: true}, points: {show: true}});


                        drawGraph("#placeholder3w", [ [8,{label: "Шанс продажи", color: "rgb(50, 50, 220)"}],
                        ], gdata.gw,
                        {xaxis: xtime, yaxis: ychance, lines: {show: true}, points: {show: true}});
                        
                        drawGraph("#placeholder3m", [ [8,{label: "Шанс продажи", color: "rgb(50, 50, 220)"}],
                        ], gdata.gm,
                        {xaxis: xtime, yaxis: ychance, lines: {show: true}, points: {show: true}});


                        drawGraph("#placeholder4w", [ [5,{label: "Прибыль", color: "rgb(0, 200, 0)"}],
                        ], gdata.gw,
                        {xaxis: xtime, yaxis: ygs, lines: {show: true}, points: {show: true}});
                        
                        drawGraph("#placeholder4m", [ [5,{label: "Прибыль", color: "rgb(0, 200, 0)"}],
                        ], gdata.gm,
                        {xaxis: xtime, yaxis: ygs, lines: {show: true}, points: {show: true}});
                    }
                    );
                    //]]>
                    </script>
                """ % (jsw, jsm)
                
                s = preambule + script + "<table>%s%s</table>" % (head, body)
                
                write(iname, "%s - %s: %s" % (realm, fac, itemname(ids)), s)


    index_data = \
        h(
            u"Данные от BeanCounter (Данные: %s, генерация: %s, %s)" % \
                (
                    time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(max(lasts) if lasts else 0)),
                    time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()),
                    constant_count[0]
                )
        ) \
        + \
        ul(
            map(
                lambda realm:
                    "%s %s" %
                        (
                            realm,
                            ul(
                                map(
                                    lambda (character, f):
                                        u"%s, запас %s, данные от %s" % 
                                            (
                                                link(
                                                    "%s-%s-data-1.html" % (realm, character),
                                                    faction(f, character),
                                                    "character"
                                                ),
                                                gold(BeanCounterDB.settings[realm][character]["wealth"]),
                                                time.strftime(
                                                    "%Y-%m-%d %H:%M:%S",
                                                    time.localtime(
                                                        max(
                                                            map(
                                                                lambda transaction: int(transaction.time),
                                                                getrows(data[realm][character])
                                                            )
                                                        )
                                                    )
                                                )
                                            ),
                                    realchars[realm]
                                )
                            )
                        ),
                realchars.keys()
            )
        )

    index_summary = h(u"Статистика") + \
        ul(
        map(
        lambda realm:
            "%s: %s" % (realm, ", ".join(
                map(
                    lambda fac:
                        link("%s-%s.html" % (realm, fac), faction(fac)),
                        markets[realm].keys()
                )
            )
            ),
        markets.keys())
        )

    index = p(index_data) + p(index_summary)

    write("index", u"Отчёты BeanCounter", index)

main()
