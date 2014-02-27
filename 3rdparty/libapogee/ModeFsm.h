/*! 
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright(c) 2010 Apogee Instruments, Inc. 
* \class ModeFsm 
* \brief This is class is the implementation of the finite state machine (fsm) for camera modes 
* 
*/ 


#ifndef MODEFSM_INCLUDE_H__ 
#define MODEFSM_INCLUDE_H__ 

#include "CameraInfo.h" 
#include <string> 
#include <vector>
#include <map>
#include <stdint.h>

#ifdef WIN_OS
#include <memory>
#else
#include <tr1/memory>
#endif

class CameraIo;
class CApnCamData;

class ModeFsm 
{ 
    public: 
    

        ModeFsm( std::tr1::shared_ptr<CameraIo> & io,
             std::tr1::shared_ptr<CApnCamData> & camData,
             uint16_t rev);
        virtual ~ModeFsm();

        Apg::CameraMode GetMode() { return m_mode; }
        void SetMode( Apg::CameraMode newMode );

        void SetBulkDownload( bool TurnOn );
        bool IsBulkDownloadOn() { return m_IsBulkDownloadOn; }

        void SetExternalTrigger( bool TurnOn, Apg::TriggerMode trigMode,
            Apg::TriggerType trigType);

        std::vector< std::pair<Apg::TriggerMode,Apg::TriggerType> > GetTrigsThatAreOn();

        void SetFastSequence( bool TurnOn );
        bool IsFastSequenceOn();

        void UpdateApnCamData( std::tr1::shared_ptr<CApnCamData> & newCamData );

        void SetTdiRows( uint16_t rows );
        uint16_t GetTdiRows() { return m_TdiRows; }

        // ****** PURE VIRTUAL INTERFACE ********
        virtual bool IsTdiAvailable() = 0;
        virtual bool IsKineticsAvailable() = 0;
        virtual bool IsContinuousImagingAvailable() = 0;
        virtual bool IsTriggerNormEachOn() = 0;
        virtual bool IsTriggerNormGroupOn() = 0;
        virtual bool IsTriggerTdiKinEachOn()= 0;
        virtual bool IsTriggerTdiKinGroupOn() = 0;
        virtual bool IsTriggerExternalShutterOn() = 0;
        virtual bool IsTriggerExternalReadoutOn() = 0;

    protected:

         bool IsModeValid( Apg::CameraMode newMode );
         void ExitOldMode();

        void EnterNewMode( Apg::CameraMode newMode );
        uint16_t GetNormTrigMask( 
            Apg::TriggerType trigType);
        uint16_t GetTdiKinTrigMask( 
            Apg::TriggerType trigType);
        void TurnTrigOn(uint16_t mask);
        void TurnTrigOff(uint16_t mask);

        void EnableIoPortBit();
        void DisableIoPortBit();
        bool IsInterlineCcd();

        void SetNormTdiKinTriggers( bool TurnOn, 
                                 Apg::TriggerMode trigMode,
                                 Apg::TriggerType trigType);

        void SetShutterTrigger( bool TurnOn );
        void SetReadoutIoTrigger( bool TurnOn );

        void SetNormTrigger( const bool TurnOn, 
                                 const Apg::TriggerType trigType);

        void SetTdiKinTrigger( const bool TurnOn, 
                                 const Apg::TriggerType trigType);

         // ****** PURE VIRTUAL INTERFACE ********
        virtual bool IsExternalTriggerAvailable( Apg::TriggerMode trigMode ) = 0;

        Apg::CameraMode m_mode;
        std::tr1::shared_ptr<CameraIo> m_CamIo;
        std::tr1::shared_ptr<CApnCamData> m_CamData;
        uint16_t m_FirmwareVersion;

        bool m_IsBulkDownloadOn;
        bool m_IsFastSequeceOn;

     private:
         std::string m_fileName;
         uint16_t m_TdiRows;

        //disabling the copy ctor and assignment operator
        //generated by the compiler - don't want them
        //Effective C++ Item 6
        ModeFsm(const ModeFsm&);
        ModeFsm& operator=(ModeFsm&);
        

}; 


#endif
