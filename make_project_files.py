#!/usr/bin/python3

import xml.etree.ElementTree as ET
import re, os, sys

base_config = (
"""<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_project_file>
    <FileVersion major="1" minor="6" />
    <Project>
        <!-- <Option title="CHAPTER_HERE" /> -->
        <Option pch_mode="2" />
        <Option compiler="gcc" />
        <Build>
            <Target title="Debug">
                <Option output="bin/Debug/program" prefix_auto="1" extension_auto="1" />
                <Option object_output="obj/Debug/" />
                <Option type="1" />
                <Option compiler="gcc" />
                <Compiler>
                    <Add option="-g" />
                </Compiler>
            </Target>
            <Target title="Release">
                <Option output="bin/Release/program" prefix_auto="1" extension_auto="1" />
                <Option object_output="obj/Release/" />
                <Option type="1" />
                <Option compiler="gcc" />
                <Compiler>
                    <Add option="-O2" />
                </Compiler>
                <Linker>
                    <Add option="-s" />
                </Linker>
            </Target>
        </Build>
        <Compiler>
            <Add option="-Wall" />
            <Add option="-Wextra" />
            <Add option="-std=c++11" />
            <Add option="-pedantic" />
        </Compiler>
        <!-- <Unit filename="FILE_HERE.cpp" /> -->
        <Extensions>
            <envvars />
            <code_completion />
            <debugger />
            <lib_finder disable_auto="1" />
        </Extensions>
    </Project>
</CodeBlocks_project_file>
""")

def make_chapter_name(dirname):
    return dirname.replace(' - ', ' ').replace(' ', '_').lower()

def get_code_files(dirname):
    return [x for x in os.listdir(dirname) if x.endswith('.cpp')]

def make_config(dirname):
    files = get_code_files(dirname)
    if not files:
        return
    chapter_name = make_chapter_name(dirname)
    config = ET.ElementTree(ET.fromstring(base_config))
    project = config.find("Project")
    title = ET.Element("Option", {'title': chapter_name})
    project.append(title)
    for file in files:
        unit = ET.Element("Unit", {'filename': file})
        project.append(unit)
    project_file_name = '{}/{}.cbp'.format(dirname, chapter_name)
    config.write(project_file_name)

def main():
    for dirname in sys.argv[1:]:
        try:
            make_config(dirname)
        except Exception as e:
            print("failed:", dirname, e)

main()
