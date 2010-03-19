# -*- coding: utf-8 -*-

from django.template.loader import get_template
from django.template import Context
from django.http import HttpResponse
from django.shortcuts import render_to_response

def Main(request):
    return render_to_response('main.html', {})

def About(request):
    return render_to_response('about.html', {})

def Contacts(request):
    return render_to_response('contacts.html', {})