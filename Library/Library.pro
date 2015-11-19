#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T17:16:15
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    dao/daouser.cpp \
    model/user.cpp \
    ui/uilogon.cpp \
    core/librarycore.cpp \
    model/sysenviroment.cpp \
    ui/busywaitdialog.cpp \
    model/readers.cpp \
    model/managers.cpp \
    model/usertype.cpp \
    model/borrow.cpp \
    model/memberlevel.cpp \
    model/lossreporting.cpp \
    model/books.cpp \
    model/bookcategory.cpp \
    dao/basedao.cpp \
    dao/daobooks.cpp \
    dao/daobookcategory.cpp \
    dao/daoborrow.cpp \
    dao/daolossreporting.cpp \
    dao/daomemberlevel.cpp \
    dao/daoreaders.cpp \
    dao/daousertype.cpp \
    dao/daomanagers.cpp \
    ui/iconedlineedit.cpp \
    core/sysinfoio.cpp \
    ui/uiregister.cpp \
    core/systype.cpp \
    ui/uibookmanage.cpp \
    ui/uiusermanage.cpp \
    ui/uibookmanagetree.cpp \
    ui/uibookinformationmanage.cpp \
    ui/uibookeditmanage.cpp \
    ui/uiusermanagetree.cpp \
    ui/uiuserinformationmanage.cpp \
    ui/uiusereditmanage.cpp \
    model/uniquebook.cpp \
    dao/daouniquebook.cpp \
    ui/uiuserlibrary.cpp \
    ui/uiusercenter.cpp \
    ui/myinfowidget.cpp \
    ui/mylibrarywidget.cpp \
    ui/booklistview.cpp \
    ui/bookgroupbox.cpp \
    ui/booklistwidget.cpp \
    ui/bookui.cpp \
    ui/mylibrarybox.cpp \
    ui/uilendbook.cpp \
    ui/customdialog.cpp \
    ui/titlebar.cpp \
    ui/newbookui.cpp \
    ui/uiusertype.cpp \
    ui/uimemberlevel.cpp \
    ui/uibookcategory.cpp \
    ui/uiadmin.cpp \
    ui/addmemberlevel.cpp \
    ui/addbookcategory.cpp \
    ui/addbasewidget.cpp \
    ui/addmanager.cpp \
    ui/addmanagerbtn.cpp \
    ui/editmanagerbtn.cpp \
    ui/booktypelistview.cpp \
    ui/mylibrarylistview.cpp

HEADERS  += mainwindow.h \
    dao/daouser.h \
    model/user.h \
    ui/uilogon.h \
    core/librarycore.h \
    model/sysenviroment.h \
    ui/busywaitdialog.h \
    model/readers.h \
    model/managers.h \
    model/usertype.h \
    model/borrow.h \
    model/memberlevel.h \
    model/lossreporting.h \
    model/books.h \
    model/bookcategory.h \
    dao/basedao.h \
    dao/daobooks.h \
    dao/daobookcategory.h \
    dao/daoborrow.h \
    dao/daolossreporting.h \
    dao/daomemberlevel.h \
    dao/daoreaders.h \
    dao/daousertype.h \
    dao/DaoHeader.h \
    dao/daomanagers.h \
    ui/iconedlineedit.h \
    core/sysinfoio.h \
    ui/uiregister.h \
    core/sysinclude.h \
    core/systype.h \
    ui/uibookmanage.h \
    ui/uiusermanage.h \
    ui/uibookmanagetree.h \
    ui/uibookinformationmanage.h \
    ui/uibookeditmanage.h \
    ui/uiusermanagetree.h \
    ui/uiuserinformationmanage.h \
    ui/uiusereditmanage.h \
    model/uniquebook.h \
    dao/daouniquebook.h \
    ui/uiuserlibrary.h \
    ui/uiusercenter.h \
    ui/myinfowidget.h \
    ui/mylibrarywidget.h \
    ui/booklistview.h \
    ui/bookgroupbox.h \
    ui/booklistwidget.h \
    ui/bookui.h \
    ui/mylibrarybox.h \
    ui/uilendbook.h \
    ui/customdialog.h \
    ui/titlebar.h \
    ui/newbookui.h \
    ui/uiusertype.h \
    ui/uimemberlevel.h \
    ui/uibookcategory.h \
    ui/uiadmin.h \
    ui/addmemberlevel.h \
    ui/addbookcategory.h \
    ui/addbasewidget.h \
    ui/addmanager.h \
    ui/addmanagerbtn.h \
    ui/editmanagerbtn.h \
    ui/booktypelistview.h \
    ui/mylibrarylistview.h

FORMS    += mainwindow.ui \
    ui/uibookmanage.ui

RESOURCES += \
    images/qrc.qrc

OTHER_FILES +=
