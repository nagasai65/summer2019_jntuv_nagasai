from django.views import View
from django.contrib.auth.mixins import LoginRequiredMixin
from django.urls import resolve
from django.shortcuts import *
from onlineapp.forms.college import *
from django.contrib.auth.models import Permission
class CollegeView(LoginRequiredMixin,View):

    login_url = 'login_form'
    def get(self,request,*args,**kwargs):

        if kwargs:
            #college=College.objects.get(**kwargs)
            college=get_object_or_404(College,**kwargs)
            students=list(college.student_set.order_by('college__name'))
            return render(
                request,
                template_name="onlineapp/stdinfo.html",
                context={
                    'std':students,
                    'clg_name':college.name
                }
            )
        colleges=College.objects.all()
        return render(
            request,
            template_name="onlineapp/colleges.html",
            context={
                'colleges':colleges,
                'title':'college app',
                'perm':request.user.get_all_permissions(),
            }
        )

class AddCollege(View):
    def get(self, request, *args, **kwargs):
        form=clgForm()
        if kwargs:
            if resolve(request.path_info).url_name=="delete_college":
                College.objects.get(pk=kwargs.get("pk")).delete()
                return redirect('colleges_html')
            college = College.objects.get(**kwargs)
            form=clgForm(instance=college)

        return render(
            request,
            template_name="onlineapp/addcollege.html",
            context={'form': form}
        )

    def post(self, request, *args, **kwargs):
        if resolve(request.path_info).url_name=="edit_college":
            college = College.objects.get(pk=kwargs.get("pk"))
            form = clgForm(request.POST,instance=college)
            if form.is_valid():
                form.save()
            return redirect('colleges_html')

        form = clgForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('colleges_html')

        return render(
            request,
            template_name="onlineapp/addcollege.html",
            context={'form': form}
        )