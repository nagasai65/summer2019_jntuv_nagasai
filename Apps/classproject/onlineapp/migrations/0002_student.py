# Generated by Django 2.2.1 on 2019-06-06 09:51

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('onlineapp', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Student',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=128)),
                ('dob', models.DateField()),
                ('db_folder', models.CharField(max_length=64)),
                ('email', models.EmailField(max_length=254)),
                ('dropped_out', models.BooleanField()),
                ('colege', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='onlineapp.College')),
            ],
        ),
    ]
