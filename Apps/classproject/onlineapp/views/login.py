from django.views import View
from onlineapp.forms import *
from django.shortcuts import *
from django.urls import resolve
from django.contrib.auth import authenticate,login,logout
from django.contrib import messages


def logout_fun(request):
    logout(request)
    return redirect('login_form')


class LoginView(View):
    def get(self,request):
        if request.user.is_authenticated :
            return redirect("colleges_html")
        form=LoginForm()
        return render(
            request,
            template_name="onlineapp/login.html",
            context={
                'form':form
            }
        )

    def post(self,request):
        form = LoginForm(request.POST)
        if form.is_valid():
            username=request.POST['username']
            password=request.POST['password']
            user=authenticate(
                request,username=username,password=password
            )
            if user is not None:
                login(request,user)
                return  redirect("colleges_html")
            else:
                messages.error(request,"User not exist")
        return redirect("login_form")