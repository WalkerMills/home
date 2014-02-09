--{{{ Main
local awful = require("awful")
require("awful.util")

theme = {}

home          = "/home/walker"
config        = home .. "/.config/awesome"
icons         = config .. "/icons"

local wallpapers =
{
    home .. "/pictures/wg/abstract/8f2817b986487a1724887649826d7f85.jpg",
    home .. "/pictures/wg/abstract/1342785494029.jpg",
    home .. "/pictures/wg/space/1370139726202.jpg",
    home .. "/pictures/wg/plain/129529188571.png"
}

theme.wallpaper = wallpapers[4]

if not awful.util.file_readable(theme.wallpaper) then
    local f = io.popen("find " .. home .. "/pictures/wg -readable -type f | grep -v templates | shuf -n 1 | xargs echo -n")
    theme.wallpaper = f:read("*all")
    f:close()
end


-- Styles
theme.font      = "Terminus 8"

-- Colors
theme.fg_normal = "#DCDCCC"
theme.fg_focus  = "#7177A6"
theme.fg_urgent = "#D23D3D"
theme.bg_normal = "#1B1B1B"
theme.bg_focus  = "#121212"
theme.bg_urgent = "#1B1B1B"

-- Borders
theme.border_width  = "0"
theme.border_normal = "#1B1B1B"
theme.border_focus  = "#6F6F6F"
theme.border_marked = "#D23D3D"

-- Titlebars
theme.titlebar_bg_focus  = "#1B1B1B"
theme.titlebar_bg_normal = "#1B1B1B"
-- theme.titlebar_[normal|focus]

-- Widgets
theme.fg_widget        = "#AECF96"
theme.fg_center_widget = "#88A175"
theme.fg_end_widget    = "#FF5656"
theme.fg_off_widget    = "#494B4F"
theme.fg_netup_widget  = "#7F9F7F"
theme.fg_netdn_widget  = "#D23D3D"
theme.bg_widget        = "#1B1B1B"
theme.border_widget    = "#1B1B1B"

-- Mouse finder
theme.mouse_finder_color = "#D23D3D"
-- theme.mouse_finder_[timeout|animate_timeout|radius|factor]

-- Tooltips
-- theme.tooltip_[font|opacity|fg_color|bg_color|border_width|border_color]

-- Taglist and Tasklist
-- theme.[taglist|tasklist]_[bg|fg]_[focus|urgent]

-- Menu
-- theme.menu_[bg|fg]_[normal|focus]
-- theme.menu_[height|width|border_color|border_width]


-- Icons

-- Taglist icons
theme.taglist_squares_sel   = icons .. "/taglist/squarefz.png"
theme.taglist_squares_unsel = icons .. "/taglist/squareza.png"
--theme.taglist_squares_resize = "false"

-- Misc icons
theme.menu_submenu_icon      = icons .. "/submenu.png"
theme.awesome_icon           = icons .. "/awesome-icon2.png"

-- Layout icons
theme.layout_tile       = icons .. "/layouts/tile.png"
theme.layout_tileleft   = icons .. "/layouts/tileleft.png"
theme.layout_tilebottom = icons .. "/layouts/tilebottom.png"
theme.layout_tiletop    = icons .. "/layouts/tiletop.png"
theme.layout_fairv      = icons .. "/layouts/fairv.png"
theme.layout_fairh      = icons .. "/layouts/fairh.png"
theme.layout_spiral     = icons .. "/layouts/spiral.png"
theme.layout_dwindle    = icons .. "/layouts/dwindle.png"
theme.layout_max        = icons .. "/layouts/max.png"
theme.layout_fullscreen = icons .. "/layouts/fullscreen.png"
theme.layout_magnifier  = icons .. "/layouts/magnifier.png"
theme.layout_floating   = icons .. "/layouts/floating.png"

-- Widget icons
theme.widget_cpu    = icons .. "/cpu.png"
theme.widget_bat    = icons .. "/bat.png"
theme.widget_mem    = icons .. "/mem.png"
theme.widget_fs     = icons .. "/diskette.png"
theme.widget_net    = icons .. "/net_down_03.png"
theme.widget_netup  = icons .. "/net_up_03.png"
theme.widget_mail   = icons .. "/mail.png"
theme.widget_vol    = icons .. "/spkr_01.png"
theme.widget_org    = icons .. "/cal.png"
theme.widget_date   = icons .. "/clock.png"
theme.widget_crypto = icons .. "/crypto.png"

-- Titlebar icons
theme.titlebar_close_button_focus  = icons .. "/titlebar/close_focus.png"
theme.titlebar_close_button_normal = icons .. "/titlebar/close_normal.png"

theme.titlebar_ontop_button_focus_active    = icons .. "/titlebar/ontop_focus_active.png"
theme.titlebar_ontop_button_normal_active   = icons .. "/titlebar/ontop_normal_active.png"
theme.titlebar_ontop_button_focus_inactive  = icons .. "/titlebar/ontop_focus_inactive.png"
theme.titlebar_ontop_button_normal_inactive = icons .. "/titlebar/ontop_normal_inactive.png"

theme.titlebar_sticky_button_focus_active    = icons .. "/titlebar/sticky_focus_active.png"
theme.titlebar_sticky_button_normal_active   = icons .. "/titlebar/sticky_normal_active.png"
theme.titlebar_sticky_button_focus_inactive  = icons .. "/titlebar/sticky_focus_inactive.png"
theme.titlebar_sticky_button_normal_inactive = icons .. "/titlebar/sticky_normal_inactive.png"

theme.titlebar_floating_button_focus_active    = icons .. "/titlebar/floating_focus_active.png"
theme.titlebar_floating_button_normal_active   = icons .. "/titlebar/floating_normal_active.png"
theme.titlebar_floating_button_focus_inactive  = icons .. "/titlebar/floating_focus_inactive.png"
theme.titlebar_floating_button_normal_inactive = icons .. "/titlebar/floating_normal_inactive.png"

theme.titlebar_maximized_button_focus_active    = icons .. "/titlebar/maximized_focus_active.png"
theme.titlebar_maximized_button_normal_active   = icons .. "/titlebar/maximized_normal_active.png"
theme.titlebar_maximized_button_focus_inactive  = icons .. "/titlebar/maximized_focus_inactive.png"
theme.titlebar_maximized_button_normal_inactive = icons .. "/titlebar/maximized_normal_inactive.png"

return theme
