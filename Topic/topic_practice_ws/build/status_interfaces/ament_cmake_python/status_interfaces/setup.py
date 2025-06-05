from setuptools import find_packages
from setuptools import setup

setup(
    name='status_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('status_interfaces', 'status_interfaces.*')),
)
