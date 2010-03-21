# -*- coding: utf-8 -*-

from ragendja.template import render_to_response

def Main(request):
    return render_to_response(request, 'main.html', {})

def About(request):
    return render_to_response(request, 'about.html', {})

def Contacts(request):
    return render_to_response(request, 'contacts.html', {})

