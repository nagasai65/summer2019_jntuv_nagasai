from rest_framework.authentication import SessionAuthentication, BasicAuthentication
from rest_framework.views import APIView
from onlineapp.serializers import *
from rest_framework.response import Response
from onlineapp.models import *
from rest_framework import viewsets, status
from onlineapp.serializers import StudentSerializer,MocktestSerializer
from rest_framework.permissions import IsAuthenticated

class StudentView(APIView):
    authentication_classes = (SessionAuthentication, BasicAuthentication)
    permission_classes = (IsAuthenticated,)
    def get(self, request,  **kwargs):
        if ("id" not in kwargs):
            college = College.objects.get(pk=kwargs.get("pk"))
            students = Student.objects.filter(college=college)
            serializer = StudentDataSerializer(students, many=True)
            return Response(serializer.data, status=status.HTTP_200_OK)
        else:
            students = Student.objects.get(id=kwargs.get("id"))
            serializer = StudentDataSerializer(students)
            return Response(serializer.data, status=status.HTTP_200_OK)

    def post(self, request, **kwargs):
        college = College.objects.get(pk=kwargs.get("pk"))
        student = Student(college=college)
        studentserialzer = StudentSerializer(data=request.data, instance=student)
        if studentserialzer.is_valid():
            studentserialzer.save()
        else:
            return Response(studentserialzer.data, status=status.HTTP_400_BAD_REQUEST)
        mocktest = MockTest1(student=student)
        mocktestserializer = MocktestSerializer(data=request.data['mocktest1'], instance=mocktest)
        if mocktestserializer.is_valid():
            mocktestserializer.save()
            studentserialzer.data.update({"mocktest1": mocktestserializer.data})
            return Response(studentserialzer.data, status=status.HTTP_200_OK)
        return Response(studentserialzer.data, status=status.HTTP_400_BAD_REQUEST)

    def put(self, request, **kwargs):
        student = Student.objects.get(id=kwargs.get("id"))
        mocktest = MockTest1.objects.get(student=student)
        studentserialzer = StudentSerializer(data=request.data, instance=student)
        if studentserialzer.is_valid():
            studentserialzer.save()
        else:
            return Response(studentserialzer.data, status=status.HTTP_400_BAD_REQUEST)
        mocktestserializer = MocktestSerializer(data=request.data['mocktest1'], instance=mocktest)
        if mocktestserializer.is_valid():
            mocktestserializer.save()
            studentserialzer.data.update({"mocktest1": mocktestserializer.data})
            return Response(studentserialzer.data, status=status.HTTP_200_OK)
        return Response(studentserialzer.data, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, **kwargs):
        student = Student.objects.get(id=kwargs.get("id"))
        student.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
