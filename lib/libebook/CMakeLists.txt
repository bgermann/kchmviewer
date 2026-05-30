# Project files
SET( libebookSources
    ebook_chm.cpp
    ebook_epub.cpp
    ebook.cpp
    ebook_chm_encoding.cpp
    ebook_search.cpp
    helper_entitydecoder.cpp
    helper_search_index.cpp
    helperxmlhandler_epubcontainer.cpp
    helperxmlhandler_epubcontent.cpp
    helperxmlhandler_epubtoc.cpp
 )

add_library( ebook STATIC ${libebookSources} )

target_link_libraries( ebook Qt6::Core Qt6::Widgets Qt6::Xml )

