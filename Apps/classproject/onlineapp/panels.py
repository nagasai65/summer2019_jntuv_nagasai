from debug_toolbar.panels import DebugPanel
from django.template.loader import render_to_string
from django.utils.translation import ugettext_lazy as _
from django.shortcuts import render
import os
class SysInfo(DebugPanel):
    name='SysInfo'
    has_content=True
    template = 'onlineapp/sysinfo.html'

    def nav_title(self):
        return _('System Info')

    def title(self):
        return _("System Information")

    def generate_stats(self, request, response):
        self.record_stats(
            {
                'one':{
                    'o':10
                },
                'two':{
                    'o':0
                }
            }
        )