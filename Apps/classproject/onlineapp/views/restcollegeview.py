from  rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.response import Response
from onlineapp.serializers import CollegeSerializer
from onlineapp.models import College

@api_view(['GET','POST'])
def college_list(request):
    if request.method == 'GET':
        colleges=College.objects.all()
        serializer=CollegeSerializer(colleges,many=True)
        return Response(serializer.data)
    elif request.method == 'POST':
        serializer=CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data,status=status.HTTP_201_CREATED)
        return Response(serializer.errors,status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET','PUT','DELETE'])
def college_details(request,pk):
    try:
        college=College.objects.get(pk=pk)
    except College.DoesNotExist:
        return Response(status=status.HTTP_404_NOT_FOUND)
    if request.method == "GET":
        serializer=CollegeSerializer(college)
        return Response(serializer.data)
    elif request.method == "PUT":
        serializer=CollegeSerializer(college,data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors,status=status.HTTP_400_BAD_REQUEST)
    elif request.method == "DELETE":
        college.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)

