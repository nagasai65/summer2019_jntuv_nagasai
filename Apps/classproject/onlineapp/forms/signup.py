from django import forms


class SignupForm(forms.Form):

    first_name=forms.CharField(
        max_length=30,
        widget=forms.TextInput(
            attrs={'class':'input',
                   'placeholder':'First name'
                   }
        )
    )
    last_name =forms.CharField(
        max_length=30,
        widget=forms.TextInput(
            attrs={'class':'input',
                   'placeholder':'lastname'
                   }
        )
    )
    username = forms.CharField(
        max_length=30,
        widget=forms.TextInput(
            attrs={'class': 'input',
                   'placeholder': 'Username'
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
