from django.views import View
from django.shortcuts import *
from django.urls import resolve
from onlineapp.forms.student import *

class StdView(View):
    def get(self,request,*args,**kwargs):
        stdform = StdForm()
        marksform = MarksForm()
        if kwargs:
            if resolve(request.path_info).url_name=="delete_student":
                Student.objects.get(id=kwargs.get("id")).delete()
                return redirect("college_html")
            college=College.objects.get(pk=kwargs.get("pk"))
            student=Student(college=college)
            stdform = StdForm(instance=student)
            marks=MockTest1(student=student)
            marksform=MarksForm(instance=marks)

        return render(
            request,
            template_name="onlineapp/addstudent.html",
            context={
                'stdform':stdform,
                'marksform':marksform
            }
        )


    def post(self,request,*args,**kwargs):
        if resolve(request.path_info).url_name=='edit_student':
            student=Student.objects.get(pk=kwargs.get("id"))
            stdform=StdForm(request.POST,instance=student)
            if stdform.is_valid():
                stdform.save()
                mocktest=MockTest1.objects.get(student=student)
                total = 0
                stri = "problem"
                for i in range(1, 5):
                    total += int(request.POST[stri + str(i)])
                mocktest.total = total
                marksform=MarksForm(request.POST,instance=mocktest)

                if marksform.is_valid():
                    marksform.save()
            return redirect("college_details")
        if resolve(request.path_info).url_name == 'add_student':
            college=College.objects.get(pk=kwargs.get("pk"))
            student=Student(college=college)
            stdform=StdForm(request.POST,instance=student)
            if stdform.is_valid():
                stdform.save()
                mocktest=MockTest1(student=student)
                total=0
                stri="problem"
                for i in range(1,5):
                    total+=int(request.POST[stri+str(i)])
                mocktest.total=total
                marksform=MarksForm(request.POST,instance=mocktest)
                if marksform.is_valid():
                    marksform.save()
            return redirect("colleges_html")