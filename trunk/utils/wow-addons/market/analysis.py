#!/usr/bin/python
# -*- coding: utf8 -*-

from BeanCounterDB import data
import os

#### some html helpers

htmldir = "html"
dbversion = "2.09"

def write(fn, title, body):
    if type(title)==type(u""): title = title.encode("utf8")
    if type(body)==type(u""): body = body.encode("utf8")
    fname = os.path.join(htmldir, fn+".html")
    f = file(fname, "w")
    text = u"""<html>
    <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>%s</title>
    <link rel="stylesheet" href="style.css" type="text/css"/>
    <!-- WoWHead MouseOver-Tooltip -->
    <script src="http://ru.wowhead.com/widgets/power.js" type="text/javascript"></script>
    <!-- /WoWHead MouseOver-Tooltip -->
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
    <div id="footer"><small>Made by kreved::)</small></div>
    </body>
    </html>""".encode("utf8") % (title, body)
    f.write(text)
    f.close()

def ul(t, cls="default"):
    return "<ul class='%s'>%s</ul>" % (cls, "\n".join(map(lambda x: "<li>%s</li>" % x, t)))

def link(href, text, cls="default"):
    return "<a class='%s' href='%s'>%s</a>" % (cls, href, text)

def p(text, cls="p"):
    return "<div class='%s'>%s</div>" % (cls, text)

def div(text, cls="default"):
    return "<div class='%s'>%s</div>" % (cls, text)

def span(text, cls="default"):
    return "<span class='%s'>%s</span>" % (cls, text)

def table(text, cls="listview-mode-default"):
    return """<div class="listview"><table class='%s'>%s</table></div>""" % (cls, text)

def thead(text, cls="default"):
    return "<thead class='%s'>%s</thead>" % (cls, text)

def tbody(text, cls="default"):
    #print "before joining"
    #text = "\n".join(t)
    #print "after joining"
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
    if f=="Alliance": return span(text, "alliance-icon")
    if f=="Horde": return span(text, "horde-icon")
    return span(text, "unknown-faction")

def gold(amount):
    amount = int(amount)
    g = amount/10000
    s = amount/100%100
    c = amount % 100
    if g>0:
        return """<span class="moneygold">%d</span><span class="moneysilver">%d</span><span class="moneycopper">%d</span>""" % (g, s, c)
    elif s>0:
        return """<span class="moneysilver">%d</span><span class="moneycopper">%d</span>""" % (s, c)
    else: return """<span class="moneycopper">%d</span>""" % c

def itemlink(ids, item):
    #import code; code.interact(local=locals())
    color, name = item.split(";")
    itemid = ids.split(":")[0]
    color = color[3:]
    return """<a class='itemlink' href="http://ru.wowhead.com/?item=%s" style="color: #%s">%s</a>""" % \
        (itemid, color, name)

#########

realms = filter(lambda x: x!="settings" and x!="ItemIDArray", data.keys())

index_data = h(u"Данные от BeanCounter") + \
    ul(map(lambda realm: "%s: %s" % (realm, ", ".join(map(
        lambda char: link(char+"-data.html", faction(data[realm][char]["faction"], char), "character"), data[realm].keys()
        ))), realms))
index_summary = h(u"Статистика")

class transaction:
    time = None
    def __init__(self, category, ids, itemstring, line):
        self.category = category
        self.ids = ids
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
        elif category=="completedBids/Buyouts":
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
    def tr(self):
        import time
        date = time.strftime("%d.%m.%Y %H:%M:%S", time.localtime(self.time))
        s = self.itemstring.split(":")
        s = s[1] + ":" + s[7]
        item = itemlink(self.ids, data["ItemIDArray"].get(s, "cffff1010;???"))
        if self.category=="completedAuctions":
            action = u"Продано"
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
        elif self.category=="completedBids/Buyouts":
            stack = int(self.stack)
            if self.bid!=self.buyout:
                action = u"Выиграно"
                price = int(self.bid)
            else:
                action = u"Куплено"
                if self.buyout: price = int(self.buyout)
                else: price = 0
            pprice = gold(price / stack)
            price = gold(price)
            if not self.buyout:
                price = "???"
                pprice = "???"
            buyer_seller = self.seller
            fee_depo = ""
        elif self.category=="failedAuctions":
            action = u"Не продано"
            stack = int(self.stack)
            price = int(self.buyout)
            pprice = gold(price/stack)
            price = gold(price)
            buyer_seller = ""
            fee_depo = gold(int(self.deposit))
        else: raise ValueError()
        return tr(td(date)+td(action)+td(item)+td(stack)+td(price)+td(pprice)+td(fee_depo)+td(small(buyer_seller)))

def getrows(c):
    return \
        sum( # суммируем по категориям
            map(
                lambda category:
                    sum( # суммируем по itemid
                        map(
                            lambda (itemids, itemidset):
                                sum( # суммируем по itemstring
                                    map(
                                        lambda itemstring:
                                            map(
                                                lambda info:
                                                    transaction(category, itemids, itemstring, info),
                                                itemidset[itemstring].values()
                                            ),
                                        itemidset.keys()
                                    ),
                                []),
                            c[category].items()
                        ),
                        []
                    ),
                ("completedAuctions", "failedAuctions", "completedBids/Buyouts")
            ),
            []
        )

import gc

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

for realm in realms:
    chars = data[realm].keys()
    for char in chars:
        c = data[realm][char]
        f = c["faction"]
        cversion = data[realm][char]["version"]
        if cversion != dbversion:
            write(char+"-data", u"История торговли %s" % char, \
                p(u"""База, полученная от BeanCounter для %s имеет версию "%s", а этот
                скрипт умеет работать только с базами версии "%s".""" % \
                (char, cversion, dbversion)))
            continue
        log = getrows(c)
        log.sort(key=lambda x: -x.time)
        s = h(u"%s, %s" % (faction(f, char), gold(c["wealth"]))).encode("utf8") + \
            table(
                thead(tr(th(u"Дата")+th(u"Действие")+th(u"Предмет")+th(u"Стек")+th(u"Стоимость")+th(u"За штуку")+th(u"fee/deposit")+th(u"Игрок"))).encode("utf8")
                + "\n".join(map(lambda op: op.tr().encode("utf-8"), log))
                )
        write(char+"-data", u"История торговли %s" % char, p(s))

index = p(index_data) + p(index_summary)

write("index", u"Отчёты BeanCounter", index)
