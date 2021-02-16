#include "pch.h"
#include <api/Basic_Event.h>
#include <api/commands.h>
#include "BDS.hpp"

bool oncmd_gmode(CommandOrigin const& ori, CommandOutput& outp, CommandSelector<Player>& s, int mode) {
	auto res = s.results(ori);
	if (!Command::checkHasTargets(res, outp)) return false;
	for (auto i : res) {
		setPlayerGameType(i, mode);
	}
	return true;
}

void REGCMD() {
	Event::addEventListener([](RegCmdEV e) {
		CMDREG::SetCommandRegistry(e.CMDRg);
		MakeCommand("gmode", "set your gametype", 1);
		CmdOverload(gmode, oncmd_gmode, "target", "mode");
		});
}