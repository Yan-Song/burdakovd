# -*- coding: utf-8 -*-

from django.template.loader import get_template
from django.template import Context
from django.http import HttpResponse
from django.shortcuts import render_to_response
from django.template import RequestContext

def Main(request):
    return render_to_response('main.html', {}, context_instance=RequestContext(request))

def About(request):
    return render_to_response('about.html', {}, context_instance=RequestContext(request))

def Contacts(request):
    return render_to_response('contacts.html', {}, context_instance=RequestContext(request))

