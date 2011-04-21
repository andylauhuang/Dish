QT += sql
TARGET = dish
TEMPLATE = app
DESTDIR = ./
HEADERS += Business/DishDisplayBusiness.h \
    DAO/DishMasterDAO.h \
    UI/MainForm.h \
    UI/DishDisplay.h \
    UI/Dish.h \
    DAO/Connection.h \
    Business/MemoryTableBusiness.h \
    UI/DishPictureText.h \
    UI/SelectedDishDisplay.h \
    UI/SelectedDishItem.h \
    UI/ppt.h \
    UI/DialogLogin.h \
    DAO/TableInfoDAO.h \
    Business/DialogLoginBusiness.h \
    Business/DishSelectBusiness.h \
    DAO/OrderDetailDAO.h
SOURCES += Business/DishDisplayBusiness.cpp \
    DAO/DishMasterDAO.cpp \
    UI/MainForm.cpp \
    UI/DishDisplay.cpp \
    UI/Dish.cpp \
    main.cpp \
    Business/MemoryTableBusiness.cpp \
    UI/DishPictureText.cpp \
    UI/SelectedDishItem.cpp \
    UI/SelectedDishDisplay.cpp \
    UI/ppt.cpp \
    UI/DialogLogin.cpp \
    DAO/TableInfoDAO.cpp \
    Business/DialogLoginBusiness.cpp \
    Business/DishSelectBusiness.cpp \
    DAO/OrderDetailDAO.cpp
FORMS += UI/MainForm.ui \
    UI/SelectedDishDisplay.ui \
    UI/ppt.ui \
    UI/DialogLogin.ui
RESOURCES += dish.qrc
