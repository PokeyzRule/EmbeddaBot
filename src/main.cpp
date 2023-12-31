#include <dpp/dpp.h>

int main() {
	std::ifstream tokenfile("../BOT_TOKEN");
	std::string BOT_TOKEN;
	getline(tokenfile, BOT_TOKEN);
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

	bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
	});

	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
		}
	});

	bot.start(dpp::st_wait);
}