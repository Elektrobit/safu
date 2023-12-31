# The project documentation

Find here the efforts that are taken to document the project and how to
enhance and to extend it. 

The documentation combines different sources with different aspects.

Sources are :

* Source Code (doc-strings)
* Architecture Design Records (markdown files)
* Manuals, Howtos, Guidelines (markdown files)
* Component or topic related detailed documentation (markdown files)

The documentation shall be split into two main categories:

* *User Manual*: API-Docs, Howtos, Installation & Setup guides, public data
  description, demos, ...
* *Developer Manual*: API-Docs (including non public), developer setup, project
  guidelines, Architecture Design Records, –everything important to develop the
  project–

To generate the final documentation artefacts, the [sphinx-doc] tool is used.

[sphinx-doc]: https://www.sphinx-doc.org

## Howto build

To build the HTML version run the following:

```bash
./ci/docker-run.sh
./ci/build_doc.sh
```

Then find the documentation in `doc/build` starting with
`doc/build/index.html` as entry point.

## Documentation source structure

### API-Docu

The API-Docu is generated using the [sphinx-c-autodoc] extension. There are two API-Docus:

* User Manual API-Doc: describe all public accessible APIs for libraries to be
  used by users.
  * This usually contains only interface APIs to interact with the project
* Developer API-Doc: describe the complete API for all components of the project. 
  * This contains also internal APIs, to develop or extend the project

To see or control what will be deployed into which section of the
documentation, check the two functions `createApiDocu` and
`createDeveloperApiDocu` in `ci/build_doc.sh`.

For the API documentation the following rules shall be applied:

* Doc-String shall be added to the declaration of an element. Usually in the
  header 
* Only public linkage needs documentation, its optional to document private
  /static functions as needed.
* As format for the doc-strings the project agreed on the [Napoleon] format. 
* The doc-string shall enhance the information already given by the
  declaration.
  * Please avoid explaining what is already obvious by reading the declaration.
* Focus on a Detailed Design of the element to be documented, it shall contain:
  * Bounds of parameter
  * Direction (in/out) of parameter
  * Return value (Bounds, explain values/ranges)
  * Description of expectations of side effects (acquire resources, interact
    with system / other components)
  * Description of different behavior depending on the input.
* Think of the combination of doc-string and element declaration as a detailed
  design necessary to verify the correct behavior of function by a unit test.

[sphinx-c-autodoc]: https://github.com/speedyleion/sphinx-c-autodoc
[Napoleon]: https://sphinxcontrib-napoleon.readthedocs.io/en/latest/



