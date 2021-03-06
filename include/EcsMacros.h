/************************************************************************
ECS:Python - Light-Weight C++ Library For Embedding Python Into C++
Copyright (c) 2012-2019 Marcus Tomlinson

This file is part of EcsPython.

The BSD 2-Clause License:
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************************************/

#ifndef ECSMACROS_H
#define ECSMACROS_H

#include <string>
#include <typeinfo>
#include <vector>

//=================================================================================================

typedef struct _object PyObject;
typedef PyObject* ( *PyCFunction )( PyObject*, PyObject* );

extern int ( *_Ecs_ParseTuple )( PyObject*, const char*, ... );

//=================================================================================================

void _EcsAddNewMethod( const char* methodName, PyCFunction methodPointer, int methodFlags );

//-------------------------------------------------------------------------------------------------

template <class Type>
PyObject* _Ecs_ToPyObject( const Type& Value );

//-------------------------------------------------------------------------------------------------

PyObject* _Ecs_GetPythonNull();

//=================================================================================================
// COMMON TOOLS
// ============

template <class Type>
static void _Ecs_AppendPythonArgType( std::string& pyTypes )
{
    std::string append;

    if ( typeid( Type ) == typeid( char* ) )
        append = "s";
    else if ( typeid( Type ) == typeid( std::string ) )
        append = "s";
    else if ( typeid( Type ) == typeid( char ) )
        append = "c";
    else if ( typeid( Type ) == typeid( unsigned char ) )
        append = "b";
    else if ( typeid( Type ) == typeid( short ) )
        append = "h";
    else if ( typeid( Type ) == typeid( unsigned short ) )
        append = "H";
    else if ( typeid( Type ) == typeid( int ) )
        append = "i";
    else if ( typeid( Type ) == typeid( unsigned int ) )
        append = "I";
    else if ( typeid( Type ) == typeid( long ) )
        append = "l";
    else if ( typeid( Type ) == typeid( unsigned long ) )
        append = "k";
    else if ( typeid( Type ) == typeid( long long ) )
        append = "L";
    else if ( typeid( Type ) == typeid( unsigned long long ) )
        append = "K";
    else if ( typeid( Type ) == typeid( bool ) )
        append = "i";
    else if ( typeid( Type ) == typeid( double ) )
        append = "f";
    else if ( typeid( Type ) == typeid( float ) )
        append = "f";
    else if ( typeid( Type ) == typeid( void* ) )
        append = "K";

    pyTypes.append( append );
}

//-------------------------------------------------------------------------------------------------

template <class Type>
void _Ecs_FromPyObject( char* in, Type& out )
{
    out = (Type)in;
}

inline void _Ecs_FromPyObject( char* in, double& out )
{
    out = *(float*)&in;
}

inline void _Ecs_FromPyObject( char* in, float& out )
{
    out = *(float*)&in;
}

//-------------------------------------------------------------------------------------------------

template <class RetT>
static std::string _Ecs_MakeMethodArgs()
{
    return "";
}
template <class RetT, class A1T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a";
}
template <class RetT, class A1T, class A2T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b";
}
template <class RetT, class A1T, class A2T, class A3T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e, f";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e, f, g";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e, f, g, h";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T, class A9T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e, f, g, h, i";
}
template <class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T, class A9T, class A10T>
static std::string _Ecs_MakeMethodArgs()
{
    return ", a, b, c, d, e, f, g, h, i, j";
}

//=================================================================================================
// ECS_REGISTER_CLASS
// ==================

#define ECS_REGISTER_CLASS( Class )                                                \
    static void Ecs_Init##_##Class()                                               \
    {                                                                              \
        EcsPythonClassesDict.push_back( new EcsClass( #Class, typeid( Class ) ) ); \
        EcsPythonClassesDef.append( "class " #Class                                \
                                    ":\n\
\tdef __init__( self, ecsPtr ):\n\
\t\tself._self = ecsPtr\n\
\tdef __call__( self ):\n\
\t\treturn self._self\n" );                                                        \
    }

//=================================================================================================
// ECS_REGISTER_METHOD
// ===================

#define _MAKE_METHOD_INIT( Class, Method, ... )                           \
    static void Ecs_Init##_##Class##_##Method()                           \
    {                                                                     \
        std::string methodArgs = _Ecs_MakeMethodArgs<__VA_ARGS__>();      \
        _EcsAddNewMethod( #Class "_" #Method, Class##_##Method, 0x0001 ); \
        EcsPythonClassesDef.append( "\tdef " #Method "( self" )           \
            .append( methodArgs )                                         \
            .append(                                                      \
                " ):\n\
\t\treturn EcsPython." #Class "_" #Method "( self._self" )                \
            .append( methodArgs )                                         \
            .append( " )\n" );                                            \
    }

//-------------------------------------------------------------------------------------------------

#define _MAKE_METHOD_CALL( Class, Method )                                                                                           \
    template <class ObjT, class RetT>                                                                                                \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* obj;                                                                                                                   \
        std::string pyTypes = "K";                                                                                                   \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &obj ) )                                                                        \
            return ( RetT )( (ObjT*)obj )->Method();                                                                                 \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T>                                                                                     \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[2];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1] ) )                                                          \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1 );                                                                         \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T>                                                                          \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[3];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2] ) )                                                \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2 );                                                                     \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T>                                                               \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[4];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3] ) )                                      \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3 );                                                                 \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T>                                                    \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[5];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4] ) )                            \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4 );                                                             \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T>                                         \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[6];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5] ) )                  \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5 );                                                         \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T>                              \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[7];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A6T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5], &objs[6] ) )        \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            A6T a6;                                                                                                                  \
            _Ecs_FromPyObject( objs[6], a6 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5, a6 );                                                     \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T>                   \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[8];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A6T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A7T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5], &objs[6],           \
                              &objs[7] ) )                                                                                           \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            A6T a6;                                                                                                                  \
            _Ecs_FromPyObject( objs[6], a6 );                                                                                        \
            A7T a7;                                                                                                                  \
            _Ecs_FromPyObject( objs[7], a7 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5, a6, a7 );                                                 \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T>        \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[9];                                                                                                               \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A6T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A7T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A8T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5], &objs[6], &objs[7], \
                              &objs[8] ) )                                                                                           \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            A6T a6;                                                                                                                  \
            _Ecs_FromPyObject( objs[6], a6 );                                                                                        \
            A7T a7;                                                                                                                  \
            _Ecs_FromPyObject( objs[7], a7 );                                                                                        \
            A8T a8;                                                                                                                  \
            _Ecs_FromPyObject( objs[8], a8 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5, a6, a7, a8 );                                             \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T,        \
              class A9T>                                                                                                             \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[10];                                                                                                              \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A6T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A7T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A8T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A9T>( pyTypes );                                                                                    \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5], &objs[6], &objs[7], \
                              &objs[8], &objs[9] ) )                                                                                 \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            A6T a6;                                                                                                                  \
            _Ecs_FromPyObject( objs[6], a6 );                                                                                        \
            A7T a7;                                                                                                                  \
            _Ecs_FromPyObject( objs[7], a7 );                                                                                        \
            A8T a8;                                                                                                                  \
            _Ecs_FromPyObject( objs[8], a8 );                                                                                        \
            A9T a9;                                                                                                                  \
            _Ecs_FromPyObject( objs[9], a9 );                                                                                        \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5, a6, a7, a8, a9 );                                         \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }                                                                                                                                \
    template <class ObjT, class RetT, class A1T, class A2T, class A3T, class A4T, class A5T, class A6T, class A7T, class A8T,        \
              class A9T, class A10T>                                                                                                 \
    static RetT Class##_##Call##Method( PyObject* args, bool& success )                                                              \
    {                                                                                                                                \
        success = true;                                                                                                              \
        char* objs[11];                                                                                                              \
        std::string pyTypes = "K";                                                                                                   \
        _Ecs_AppendPythonArgType<A1T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A2T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A3T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A4T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A5T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A6T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A7T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A8T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A9T>( pyTypes );                                                                                    \
        _Ecs_AppendPythonArgType<A10T>( pyTypes );                                                                                   \
        if ( _Ecs_ParseTuple( args, pyTypes.c_str(), &objs[0], &objs[1], &objs[2], &objs[3], &objs[4], &objs[5], &objs[6], &objs[7], \
                              &objs[8], &objs[9], &objs[10] ) )                                                                      \
        {                                                                                                                            \
            A1T a1;                                                                                                                  \
            _Ecs_FromPyObject( objs[1], a1 );                                                                                        \
            A2T a2;                                                                                                                  \
            _Ecs_FromPyObject( objs[2], a2 );                                                                                        \
            A3T a3;                                                                                                                  \
            _Ecs_FromPyObject( objs[3], a3 );                                                                                        \
            A4T a4;                                                                                                                  \
            _Ecs_FromPyObject( objs[4], a4 );                                                                                        \
            A5T a5;                                                                                                                  \
            _Ecs_FromPyObject( objs[5], a5 );                                                                                        \
            A6T a6;                                                                                                                  \
            _Ecs_FromPyObject( objs[6], a6 );                                                                                        \
            A7T a7;                                                                                                                  \
            _Ecs_FromPyObject( objs[7], a7 );                                                                                        \
            A8T a8;                                                                                                                  \
            _Ecs_FromPyObject( objs[8], a8 );                                                                                        \
            A9T a9;                                                                                                                  \
            _Ecs_FromPyObject( objs[9], a9 );                                                                                        \
            A10T a10;                                                                                                                \
            _Ecs_FromPyObject( objs[10], a10 );                                                                                      \
            return ( RetT )( (ObjT*)objs[0] )->Method( a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 );                                    \
        }                                                                                                                            \
        success = false;                                                                                                             \
        return RetT();                                                                                                               \
    }

//-------------------------------------------------------------------------------------------------

#define ECS_REGISTER_METHOD_RETURN( Class, Method, ReturnType, ... )                                                     \
    _MAKE_METHOD_CALL( Class, Method )                                                                                   \
    static PyObject* Class##_##Method( PyObject*, PyObject* args )                                                       \
    {                                                                                                                    \
        bool success;                                                                                                    \
        PyObject* result = _Ecs_ToPyObject( Class##_##Call##Method<Class, ReturnType, ##__VA_ARGS__>( args, success ) ); \
        if ( success )                                                                                                   \
            return result;                                                                                               \
        else                                                                                                             \
            return NULL;                                                                                                 \
    }                                                                                                                    \
    _MAKE_METHOD_INIT( Class, Method, ReturnType, ##__VA_ARGS__ )

//-------------------------------------------------------------------------------------------------

#define ECS_REGISTER_METHOD_VOID( Class, Method, ... )                       \
    _MAKE_METHOD_CALL( Class, Method )                                       \
    static PyObject* Class##_##Method( PyObject*, PyObject* args )           \
    {                                                                        \
        bool success;                                                        \
        Class##_##Call##Method<Class, void, ##__VA_ARGS__>( args, success ); \
        if ( success )                                                       \
            return _Ecs_GetPythonNull();                                     \
        else                                                                 \
            return NULL;                                                     \
    }                                                                        \
    _MAKE_METHOD_INIT( Class, Method, void, ##__VA_ARGS__ )

//=================================================================================================

#endif  // ECSMACROS_H
