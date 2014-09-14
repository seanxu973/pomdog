#
#  Copyright (C) 2013-2014 mogemimi.
#
#  Distributed under the MIT License.
#  See accompanying file LICENSE.md or copy at
#  http://enginetrouble.net/pomdog/LICENSE.md for details.
#

# Create new project:
# >>> cd .
# >>> python pomdog/tools/quickstart.py YourProjectName
# >>> cd YourProjectName

# >>> python tools/quickstart.py ProjectName -d ~/path/gamedev -u net.example.ProjectName
# >>> cd ~/path/gamedev/ProjectName


import sys
import os
import argparse
import subprocess
import uuid
import shutil
from string import Template


def CreateProjectDirectory(path):
    if os.path.exists(path):
        print("Error: {0} is exists".format(path))
        return False, ""
    if (not os.path.exists(path)) and path:
        os.makedirs(path)
        print("{0}: Create a new directory.".format(path))
    return True, path


def ParsingCommandLineAraguments():
    parser = argparse.ArgumentParser(prog='quickstart',
                                     description='Create new project.')
    parser.add_argument('name', default='def', help='project name')
    parser.add_argument('-d', nargs=1, required=True, help='directory path')
    parser.add_argument('-u', default='com.example.QuickStart',
                        nargs=1, help='project url')
    args = parser.parse_args()
    return args


def CopyTemplates(template_directory, project_root):
    templates_list = [
        "Content",
        "Source",
        "Platform.Cocoa",
        "Build",
        "README.md",
        ".gitignore",
    ]

    for path in templates_list:
        source_path = os.path.join(template_directory, path)
        dest_path = os.path.join(project_root, path)

        if os.path.isdir(source_path):
            shutil.copytree(source_path, dest_path)
        elif os.path.exists(source_path):
            shutil.copy(source_path, dest_path)
        else:
            print("Error: Cannot find file {0}".format(source_path))


def CopyFrameworkFiles(framework_root, project_root):
    framework_list = [
        "build",
        "include",
        "src",
        "third_party/zlib",
        "third_party/libpng",
        "LICENSE.md",
        "README.md",
        ".gitignore",
    ]

    for path in framework_list:
        source_path = os.path.join(framework_root, path)
        dest_path = os.path.join(project_root, "Pomdog/" + path)

        if os.path.isdir(source_path):
            shutil.copytree(source_path, dest_path)
        elif os.path.exists(source_path):
            shutil.copy(source_path, dest_path)
        else:
            print("Error: Cannot find file {0}".format(source_path))


def RenameSourceContent(project_root, identifier, source):
    path = os.path.join(project_root, source)

    if not os.path.exists(path):
        print("Error: Cannot find file {0}".format(path))
        return

    f = open(path, 'r')
    content = f.read()
    f.close()

    f = open(path, 'w')
    content = content.replace('QuickStart', identifier)
    content = content.replace('QUICKSTART', identifier.upper())
    f.write(content)
    f.close()

def RenameContentByUrl(project_root, url, source):
    path = os.path.join(project_root, source)

    if not os.path.exists(path):
        print("Error: Cannot find file {0}".format(path))
        return

    f = open(path, 'r')
    content = f.read()
    f.close()

    f = open(path, 'w')
    content = content.replace('com.example.QuickStart', url)
    f.write(content)
    f.close()

def RenameFilename(project_root, identifier, source):
    path = os.path.join(project_root, source)

    if not os.path.exists(path):
        print("Error: Cannot find file {0}".format(path))
        return

    dest = os.path.join(project_root, source.replace('QuickStart', identifier))
    if source != dest:
        os.rename(path, dest)

def Run():
    args = ParsingCommandLineAraguments()

    #print("args = {0}".format(vars(args))) # for Debug

    args.dir = args.d[0]
    args.url = args.u[0]

    identifier = os.path.basename(args.name)
    project_root = os.path.join(args.dir, identifier)
    CreateProjectDirectory(project_root)

    #print("{0}, {1}, {2}".format(args.dir, args.url, project_root))

    framework_root = os.path.join(os.path.dirname(__file__), "..")
    templates_directory = os.path.join(framework_root,
      "templates/QuickStartApp")

    CopyTemplates(templates_directory, project_root)
    CopyFrameworkFiles(framework_root, project_root)
    RenameContentByUrl(project_root, args.url, 'Platform.Cocoa/QuickStart-Info.plist')
    RenameSourceContent(project_root, identifier, 'README.md')
    RenameSourceContent(project_root, identifier, 'Build/app.gyp')
    RenameSourceContent(project_root, identifier, 'Source/QuickStartGame.cpp')
    RenameSourceContent(project_root, identifier, 'Source/QuickStartGame.hpp')
    RenameSourceContent(project_root, identifier, 'Platform.Cocoa/AppDelegate.mm')
    RenameSourceContent(project_root, identifier, 'Platform.Cocoa/QuickStart-Info.plist')
    RenameFilename(project_root, identifier, 'Source/QuickStartGame.cpp')
    RenameFilename(project_root, identifier, 'Source/QuickStartGame.hpp')
    RenameFilename(project_root, identifier, 'Platform.Cocoa/QuickStart-Info.plist')
    RenameFilename(project_root, identifier, 'Platform.Cocoa/QuickStart-Prefix.pch')

    print("Done.")


Run()
