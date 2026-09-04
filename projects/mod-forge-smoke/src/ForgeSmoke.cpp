// SPDX-License-Identifier: GPL-2.0-or-later

#include "Config.h"
#include "Log.h"
#include "WorldScript.h"

namespace
{
class ForgeSmokeWorldScript final : public WorldScript
{
public:
    ForgeSmokeWorldScript()
        : WorldScript("ForgeSmokeWorldScript", { WORLDHOOK_ON_AFTER_CONFIG_LOAD, WORLDHOOK_ON_STARTUP })
    {
    }

    void OnAfterConfigLoad(bool reload) override
    {
        // Defaults deliberately differ from the distributed control config.
        // The log therefore distinguishes hook execution from config acceptance.
        _enabled = sConfigMgr->GetOption<bool>("ForgeSmoke.Enable", false);
        _controlValue = sConfigMgr->GetOption<uint32>("ForgeSmoke.ControlValue", 0);

        LOG_INFO("server.loading", "FORGE_SMOKE_CONFIG reload={} enabled={} control={}",
            reload ? 1 : 0, _enabled ? 1 : 0, _controlValue);
    }

    void OnStartup() override
    {
        LOG_INFO("server.loading", "FORGE_SMOKE_STARTUP enabled={} control={}",
            _enabled ? 1 : 0, _controlValue);
    }

private:
    bool _enabled = false;
    uint32 _controlValue = 0;
};
}

void Addmod_forge_smokeScripts()
{
    new ForgeSmokeWorldScript();
}
