from rest_framework import serializers
from onlineapp.models import Student,MockTest1

class StudentSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model=Student
        fields=['id','name','dob','db_folder','email','dropped_out']

class MocktestSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model=MockTest1
        fields=['id','problem1','problem2','problem3','problem4','total']

class StudentDataSerializer(serializers.HyperlinkedModelSerializer):
    mocktest1=MocktestSerializer(many=False,read_only=True)
    class Meta:
        model=Student
        fields=['id','name','dob','db_folder','email','dropped_out','mocktest1']



