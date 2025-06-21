local wezterm = require "wezterm"

local config = {}

config.color_scheme = 'Solarized (light) (terminal.sexy)'
config.enable_scroll_bar=true
config.default_cursor_style = 'BlinkingBar'
config.default_prog = { '/usr/bin/fish', '-l' }
config.warn_about_missing_glyphs = false
config.hide_tab_bar_if_only_one_tab = true

return config
