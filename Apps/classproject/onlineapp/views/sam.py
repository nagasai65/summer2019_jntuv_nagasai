from django.shortcuts import render
from django.http import *
def sam(request):
    return HttpResponse("<html><body>it is a sam response</body></html>")