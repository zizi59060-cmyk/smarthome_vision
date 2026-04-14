from setuptools import find_packages
from setuptools import setup

setup(
    name='smarthome_vision',
    version='0.0.1',
    packages=find_packages(
        include=('smarthome_vision', 'smarthome_vision.*')),
)
