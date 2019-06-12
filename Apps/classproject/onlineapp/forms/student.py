from django import forms
from onlineapp.models import *

class StdForm(forms.ModelForm):
    class Meta:
        model=Student
        exclude=['id','dob','college']
        name=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        db_folder=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        email=forms.CharField(
            widget=forms.EmailInput(attrs={'class':'input'})
        )
        dropped_out=forms.CharField(
            widget=forms.BooleanField()
        )


class MarksForm(forms.ModelForm):
    class Meta:
        model=MockTest1
        exclude=['id','student','total']
        problem1=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        problem2=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        problem3=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )
        problem4=forms.CharField(
            widget=forms.TextInput(attrs={'class':'input'})
        )