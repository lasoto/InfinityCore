/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulgurub.h"

class instance_zulgurub : public InstanceMapScript
{
    public:
        instance_zulgurub() : InstanceMapScript(ZGScriptName, 859) { }

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
                venoxisGUID     = 0;
                mandokirGUID    = 0;
                kilnaraGUID     = 0;
                zanzilGUID      = 0;
                jindoGUID       = 0;
                hazzarahGUID    = 0;
                renatakiGUID    = 0;
                wushoolayGUID   = 0;
                grilekGUID      = 0;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                   case NPC_VENOXIS:
                      venoxisGUID = creature->GetGUID();
                      break;
                   case NPC_MANDOKIR:
                      mandokirGUID = creature->GetGUID();
                      break;
                   case NPC_KILNARA:
                      kilnaraGUID = creature->GetGUID();
                      break;
                   case NPC_ZANZIL:
                      zanzilGUID = creature->GetGUID();
                      break;
                   case NPC_JINDO:
                      jindoGUID = creature->GetGUID();
                      break;
                   case NPC_HAZZARAH:
                      hazzarahGUID = creature->GetGUID();
                      break;
                   case NPC_RENATAKI:
                      renatakiGUID = creature->GetGUID();
                      break;
                   case NPC_WUSHOOLAY:
                      wushoolayGUID = creature->GetGUID();
                      break;
                   case NPC_GRILEK:
                      grilekGUID = creature->GetGUID();
                      break;
                   default:
                      break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                   case DATA_VENOXIS:
                   case DATA_MANDOKIR:
                   case DATA_KILNARA:
                   case DATA_ZANZIL:
                   case DATA_JINDO:
                   case DATA_HAZZARAH:
                   case DATA_RENATAKI:
                   case DATA_WUSHOOLAY:
                   case DATA_GRILEK:
                      break;
                   default:
                      break;
                }

                return true;
            }

            /*
            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                }
            }

            uint32 GetData(uint32 type) const
            {
                switch (type)
                {
                }

                return 0;
            }
            */

            uint64 GetData64(uint32 type) const
            {
                switch (type)
                {
                    case DATA_VENOXIS:
                        return venoxisGUID;
                    case DATA_MANDOKIR:
                        return mandokirGUID;
                    case DATA_KILNARA:
                        return kilnaraGUID;
                    case DATA_ZANZIL:
                        return zanzilGUID;
                    case DATA_JINDO:
                        return jindoGUID;
                    case DATA_HAZZARAH:
                        return hazzarahGUID;
                    case DATA_RENATAKI:
                        return renatakiGUID;
                    case DATA_WUSHOOLAY:
                        return wushoolayGUID;
                    case DATA_GRILEK:
                        return grilekGUID;
                    default:
                        break;
                }

                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "Z G " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(char const* str)
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'Z' && dataHead2 == 'G')
                {
                    for (uint8 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

        protected:
             uint64 venoxisGUID;
             uint64 mandokirGUID;
             uint64 kilnaraGUID;
             uint64 zanzilGUID;
             uint64 jindoGUID;
             uint64 hazzarahGUID;
             uint64 renatakiGUID;
             uint64 wushoolayGUID;
             uint64 grilekGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();
}
