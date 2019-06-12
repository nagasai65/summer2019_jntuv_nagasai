from onlineapp.models import College
from rest_framework import serializers

class CollegeSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model=College
        fields=('id','name','location','acronym','contact')
