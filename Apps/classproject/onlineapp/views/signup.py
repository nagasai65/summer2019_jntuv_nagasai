from django.views import View
from onlineapp.forms import *
from django.shortcuts import *
from django.contrib.auth.models import User
from django.contrib.auth import login
from django.contrib import messages
class SignupView(View):
    def get(self,request):
        form=SignupForm()

        return render(
            request,
            template_name="onlineapp/signup.html",
            context={
                'form':form
            }
        )
    def post(self,request):
        form = SignupForm(request.POST)
        if form.is_valid():
            user=User.objects.create_user(**form.cleaned_data)
            if user is not None:
                user.save()
                login(request,user)
                return redirect("colleges_html")
            else:
                messages.error("Cant create user")