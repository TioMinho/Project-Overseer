
    PROJECT OVERSEER
    Development of a System for Police Notification using C++ and SFML library.
    ============================================================================
    
    * This system was conceived as a prototype for a academic assignment of the "Software Engineering I" discipline, at the Universidade Federal do Ceará (UFC), in Brazil.
    
    The "Project Overseer" is the project of a software for Civilians to use with the purpose of inform crimes to the Police. This project wants to make automatic the process of calling the Police Call Center by using a Notification System directly to Police Cars and Policemen, abstracting the need of knowing the exact location of the occurrence, and the need to talk to a Call Center whilst the crime is taking place; as all of this can be easily archieved using technology tools as TCP/IP communication and GPS localization, far quickier than human action.

    The software is composed by four executable programs; one for each interface (Civilian, Call Center and Police Car) and one for simulate a Server.
    All the programs communicates within themselves using a TCP/IP Protocol, implemented with the SFML Socket class. The one program that simulates the Server (called "Overseer - Mainframe") has a "TCPServer" object. And all the other programs have a "TCPEntity" object (superclass of TCPServer).
    
    In addiction, a GUI was developed to be used as a Friendly-Interactive Interface. All the graphics and functionabilities of the GUI was programmed using basis SFML features.
    
    Programmed by
    Minho, 2016.
    