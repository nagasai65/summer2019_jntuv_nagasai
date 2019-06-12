from django import forms


class LoginForm(forms.Form):
    username = forms.CharField(
        max_length=30,
        widget=forms.TextInput(
            attrs={'class':'input',
                   'placeholder':'Username'
                   }
        )
    )
    password = forms.CharField(
        max_length=30,
        widget=forms.PasswordInput(
            attrs={'class': 'input',
                   'placeholder': 'Username'
                   }
        )
    )
