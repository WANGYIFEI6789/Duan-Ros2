from setuptools import find_packages, setup
from glob import glob

package_name = 'duan_autopatrol_robot'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name+"/launch", glob('launch/*.launch.py')),
        ('share/' + package_name+"/config", ['config/patrol_config.yaml']),  
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='duan',
    maintainer_email='15829054506@163.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'patrol_node=duan_autopatrol_robot.patrol_node:main',
            'speaker=duan_autopatrol_robot.speaker:main',
        ],
    },
)
