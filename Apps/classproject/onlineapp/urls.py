
from onlineapp import views

from django.contrib import admin
from django.urls import path,include
from onlineapp.views import *
from onlineapp.views import restcollegeview

urlpatterns = [

   path('api/v1/token/', generateToken.as_view(), name='token_obtain_pair'),


   path('test/',sam),
   path('api/v1/colleges/<int:pk>/students/<int:id>/',StudentView.as_view(),name='student_edit'),
   path('api/v1/colleges/<int:pk>/students/',StudentView.as_view(),name='students'),
   path('api/v1/colleges/',restcollegeview.college_list),
   path('api/v1/colleges/<int:pk>/',restcollegeview.college_details),

    path('admin/', admin.site.urls),
   # path('hello/', views.hello_world),
   # path('get_my_college/',views.get_college),
   # path('onlineapp/college_std_info/<int:index>/',views.stdinfo)

   path('colleges/',CollegeView.as_view(),name="colleges_html"),
   path('colleges/<int:pk>/',CollegeView.as_view(),name="college_details"),
   path('colleges/<str:acronym>/',CollegeView.as_view(),name="college_details"),

   path('college/add',AddCollege.as_view(),name="add_college"),
   path('colleges/<int:pk>/edit',AddCollege.as_view(),name="edit_college"),
   path('colleges/<int:pk>/delete',AddCollege.as_view(),name="delete_college"),

   path('colleges/<int:pk>/add/',StdView.as_view(),name="add_student"),
   path('colleges/<int:pk>/<int:id>/edit',StdView.as_view(),name="edit_student"),
   path('colleges/<int:pk>/<int:id>/delete',StdView.as_view(),name="delete_student"),

   path('login/',LoginView.as_view(),name="login_form"),
   path('signup/',SignupView.as_view(),name="signup_form"),
   path('logout/',logout_fun,name="logout"),
   #path('', lambda request: redirect("colleges_html")),


   ]