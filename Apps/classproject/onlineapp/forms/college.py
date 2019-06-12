from django import forms
from onlineapp.models import *

class clgForm(forms.ModelForm):
    class Meta:
        model = College
        exclude = ['id']
        name = forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        location =forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        acronym = forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        contact =forms.CharField(
            widget=forms.EmailInput(attrs={'class':'input'})
        )