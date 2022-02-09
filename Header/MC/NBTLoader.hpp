// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class NBTLoader {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_NBTLOADER
public:
    class NBTLoader& operator=(class NBTLoader const&) = delete;
    NBTLoader(class NBTLoader const&) = delete;
    NBTLoader() = delete;
#endif

public:
    /*0*/ virtual ~NBTLoader();
    /*1*/ virtual void __unk_vfn_1();
    /*2*/ virtual bool isInt() const;
    /*3*/ virtual bool isString() const;
    /*4*/ virtual bool isObject() const;
    /*5*/ virtual bool isArray() const;
    /*6*/ virtual bool doSerialize(std::string&);
    /*7*/ virtual void __unk_vfn_7();
    /*8*/ virtual bool doSerialize(float&);
    /*9*/ virtual void __unk_vfn_9();
    /*10*/ virtual void __unk_vfn_10();
    /*11*/ virtual void __unk_vfn_11();
    /*12*/ virtual void __unk_vfn_12();
    /*13*/ virtual void __unk_vfn_13();
    /*14*/ virtual void __unk_vfn_14();
    /*15*/ virtual void __unk_vfn_15();
    /*16*/ virtual void __unk_vfn_16();
    /*17*/ virtual bool doSerialize(bool&);
    /*18*/ virtual bool doBeginMember(char const*, bool);
    /*19*/ virtual bool doBeginMember(unsigned __int64, std::string&);
    /*20*/ virtual bool doEndMember();
    /*21*/ virtual bool doBeginArray(unsigned __int64&);
    /*22*/ virtual bool doBeginArrayItem(unsigned __int64);
    /*23*/ virtual bool doEndArrayItem();
    /*24*/ virtual void __unk_vfn_24();
    /*25*/ virtual bool doBeginObject();
    /*26*/ virtual bool doBeginObject(unsigned __int64&);
    /*27*/ virtual void __unk_vfn_27();
    /*28*/ virtual bool isShort() const;
    /*29*/ virtual void __unk_vfn_29();
    /*30*/ virtual bool isFloat() const;
    /*
    inline bool doSerialize(unsigned __int64& a0){
        bool (NBTLoader::*rv)(unsigned __int64&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEA_K@Z");
        return (this->*rv)(std::forward<unsigned __int64&>(a0));
    }
    inline bool doSerialize(__int64& a0){
        bool (NBTLoader::*rv)(__int64&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEA_J@Z");
        return (this->*rv)(std::forward<__int64&>(a0));
    }
    inline bool doSerialize(double& a0){
        bool (NBTLoader::*rv)(double&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAN@Z");
        return (this->*rv)(std::forward<double&>(a0));
    }
    inline bool doEndArray(){
        bool (NBTLoader::*rv)();
        *((void**)&rv) = dlsym("?doEndArray@NBTLoader@@EEAA_NXZ");
        return (this->*rv)();
    }
    inline bool doEndObject(){
        bool (NBTLoader::*rv)();
        *((void**)&rv) = dlsym("?doEndObject@NBTLoader@@EEAA_NXZ");
        return (this->*rv)();
    }
    inline bool doSerialize(signed char& a0){
        bool (NBTLoader::*rv)(signed char&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAC@Z");
        return (this->*rv)(std::forward<signed char&>(a0));
    }
    inline bool doSerialize(unsigned char& a0){
        bool (NBTLoader::*rv)(unsigned char&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAE@Z");
        return (this->*rv)(std::forward<unsigned char&>(a0));
    }
    inline bool doSerialize(unsigned short& a0){
        bool (NBTLoader::*rv)(unsigned short&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAG@Z");
        return (this->*rv)(std::forward<unsigned short&>(a0));
    }
    inline bool doSerialize(short& a0){
        bool (NBTLoader::*rv)(short&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAF@Z");
        return (this->*rv)(std::forward<short&>(a0));
    }
    inline bool doSerialize(unsigned int& a0){
        bool (NBTLoader::*rv)(unsigned int&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAI@Z");
        return (this->*rv)(std::forward<unsigned int&>(a0));
    }
    inline bool doSerialize(int& a0){
        bool (NBTLoader::*rv)(int&);
        *((void**)&rv) = dlsym("?doSerialize@NBTLoader@@EEAA_NAEAH@Z");
        return (this->*rv)(std::forward<int&>(a0));
    }
    inline bool isChar() const{
        bool (NBTLoader::*rv)() const;
        *((void**)&rv) = dlsym("?isChar@NBTLoader@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isBool() const{
        bool (NBTLoader::*rv)() const;
        *((void**)&rv) = dlsym("?isBool@NBTLoader@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline  ~NBTLoader(){
         (NBTLoader::*rv)();
        *((void**)&rv) = dlsym("??1NBTLoader@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI NBTLoader(class gsl::not_null<class CompoundTag const* >);

protected:

private:

};