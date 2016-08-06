#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <assert.h>

namespace MyZone{
    namespace Property{

        enum EN_PROPERTY_TYPE
        {
            READ_ONLY = 1,
            WRITE_ONLY = 2,
            READ_WRITE = 3
        };

        template <typename Container, typename ValueType, int nPropType>
        class __property
        {
        private:
            typedef void (Container::*SetType)(ValueType value);
            typedef ValueType (Container::*GetType)();
        private:
            __property(const __property&);
            __property& operator = (const __property&);
        public:
            __property()
            {
                m_cObject = NULL;
                Set = NULL;
                Get = NULL;
            }
            //-- This to set a pointer to the class that contain the
            //   property --
            void setContainer(Container* cObject)
            {
                m_cObject = cObject;
            }
            //-- Set the set member function that will change the value --
            void setter(SetType pSet)
            {
                if((nPropType == WRITE_ONLY) || (nPropType == READ_WRITE))
                    Set = pSet;
                else
                    Set = NULL;
            }
            //-- Set the get member function that will retrieve the value --
            void getter(GetType pGet)
            {
                if((nPropType == READ_ONLY) || (nPropType == READ_WRITE))
                    Get = pGet;
                else
                    Get = NULL;
            }
            //-- Overload the '=' sign to set the value using the set
            //   member --
            ValueType operator =(const ValueType& value)
            {
                assert(m_cObject != NULL);
                assert(Set != NULL);
                (m_cObject->*Set)(value);
                return value;
            }
            //-- To make possible to cast the property class to the
            //   internal type --
            operator ValueType()
            {
                assert(m_cObject != NULL);
                assert(Get != NULL);
                return (m_cObject->*Get)();
            }
            private:
            Container* m_cObject;  //-- Pointer to the module that
            //   contains the property --
            SetType Set;
            //-- Pointer to set member function --
            GetType Get;
            //-- Pointer to get member function --
        };

        template <typename IndexType, typename Container, typename ValueType, int nPropType>
        class __property_index
        {
        private:
            typedef void (Container::*SetType)(IndexType index, ValueType value);
            typedef ValueType (Container::*GetType)(IndexType index);
        private:
            class __property_inner
            {
            public:
                __property_inner()
                {
                    m_cObject = NULL;
                    Set = NULL;
                    Get = NULL;
                    m_Index = 0;
                }

                __property_inner& setIndex(IndexType index)
                {
                    m_Index = index;
                    return *this;
                }
                //-- This to set a pointer to the class that contain the
                //   property --
                void setContainer(Container* cObject)
                {
                    m_cObject = cObject;
                }
                //-- Set the set member function that will change the value --
                void setter(SetType pSet)
                {
                    if((nPropType == WRITE_ONLY) || (nPropType == READ_WRITE))
                        Set = pSet;
                    else
                        Set = NULL;
                }
                //-- Set the get member function that will retrieve the value --
                void getter(GetType pGet)
                {
                    if((nPropType == READ_ONLY) || (nPropType == READ_WRITE))
                        Get = pGet;
                    else
                        Get = NULL;
                }
                //-- Overload the '=' sign to set the value using the set
                //   member --
                ValueType operator =(const ValueType& value)
                {
                    assert(m_cObject != NULL);
                    assert(Set != NULL);
                    (m_cObject->*Set)(m_Index, value);
                    return value;
                }
                //-- To make possible to cast the property class to the
                //   internal type --
                operator ValueType()
                {
                    assert(m_cObject != NULL);
                    assert(Get != NULL);
                    return (m_cObject->*Get)(m_Index);
                }
                private:
                Container* m_cObject;  //-- Pointer to the module that
                //   contains the property --
                SetType Set;
                //-- Pointer to set member function --
                GetType Get;
                //-- Pointer to get member function --
                IndexType m_Index;
            };
        private:
            __property_index(const __property_index&);
            __property_index& operator = (const __property_index&);
        public:
            __property_index()
            {
            }
        public:
            __property_inner& operator [](IndexType Index)
            {
                return inner.setIndex(Index);
            }
            //-- This to set a pointer to the class that contain the
            //   property --
            void setContainer(Container* cObject)
            {
                inner.setContainer(cObject);
            }
            //-- Set the set member function that will change the value --
            void setter(SetType pSet)
            {
                inner.setter(pSet);
            }
            //-- Set the get member function that will retrieve the value --
            void getter(GetType pGet)
            {
                inner.getter(pGet);
            }

            private:
            __property_inner inner;
        };
    }
}
#endif // PROPERTY_HPP
