from setuptools import find_packages, setup

package_name = 'duanbot_application'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
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
            "init_robot_pose=duanbot_application.init_robot_pose:main",
            "get_robot_pose=duanbot_application.get_robot_pose:main",
            "nav_to_pose=duanbot_application.nav_to_pose:main",
            "waypoint_follower=duanbot_application.waypoint_follower:main",
        ],
    },
)
