/*
 * Porta-RFID.h - firmware 
 *
 * Auteur: Julio Cesar Torres (torj01)
 * SPDX-License-Identifier: LiLiQ-R-v.1.1
 * License-Filename: /LICENSE
 * Copyright (c) 2023 
 */

#ifndef Porta_RFID_h
#define Porta_RFID_h

#include "Arduino.h"

class PortaRFID {

    public: 
        void setup();
        void setupWifi(); 
        void loop(); 
        boolean validarCartao(String idCartao);    
        void acessoValido(); 
        void acessoInvalido(); 
};

#endif
