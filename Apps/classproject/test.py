import django
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE','classproject.settings')
django.setup()
from onlineapp.models import  *
College.objects.all()