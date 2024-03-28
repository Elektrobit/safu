# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import os

project = 'safu'
copyright = '2023, wolfgang.gehrhardt@emlix.com'
author = 'wolfgang.gehrhardt@emlix.com'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',

    # copy button on code blocks in HTML doc
    'sphinx_copybutton',

    # for code documentation & referencing
    'sphinx.ext.viewcode',
    'sphinx.ext.napoleon',
    'sphinx_c_autodoc',
    'sphinx_c_autodoc.napoleon',
    'sphinx_c_autodoc.viewcode',
]

templates_path = ['_templates']
exclude_patterns = []

language = 'en'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']

# c-autodoc
c_autodoc_roots = ['../../src/safu/private', '../../src/safu/public']

c_autodoc_ignore_statements = [
    '__BEGIN_DECLS',
    '__END_DECLS',
]

set_type_checking_flag = True

                                                                                                                                                          
def pre_process_C_files(app, filename, contents, *args):
    _, file_ext = os.path.splitext(filename)
    if file_ext == '.h':
        modified_contents = contents[0]
        for element in c_autodoc_ignore_statements:
            modified_contents = modified_contents.replace(element, '')
        contents[:] = [modified_contents]
                                                                                                                                                          

def setup(sphinx):
    sphinx.connect("c-autodoc-pre-process", pre_process_C_files)
