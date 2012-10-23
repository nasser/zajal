# Color::NamedColor stores colors by their name and
# transparency (alpha) level for display. Names are subjective;
# we've taken this list of colors from the X11 system, which is
# somewhat standardized.
class Color::NamedColor
  attr_accessor :name, :a

  # Here's the gigantic list of names. Brace yourself.
  COLORS = {
    indian_red: [205, 92, 92],
    light_coral: [240, 128, 128],
    salmon: [250, 128, 114],
    dark_salmon: [233, 150, 122],
    light_salmon: [255, 160, 122],
    red: [255, 0, 0],
    crimson: [220, 20, 60],
    fire_brick: [178, 34, 34],
    dark_red: [139, 0, 0],
    pink: [255, 192, 203],
    light_pink: [255, 182, 193],
    hot_pink: [255, 105, 180],
    deep_pink: [255, 20, 147],
    medium_violet_red: [199, 21, 133],
    pale_violet_red: [219, 112, 147],
    light_salmon: [255, 160, 122],
    coral: [255, 127, 80],
    tomato: [255, 99, 71],
    orange_red: [255, 69, 0],
    dark_orange: [255, 140, 0],
    orange: [255, 165, 0],
    gold: [255, 215, 0],
    yellow: [255, 255, 0],
    light_yellow: [255, 255, 224],
    lemon_chiffon: [255, 250, 205],
    light_goldenrod_yellow: [250, 250, 210],
    papaya_whip: [255, 239, 213],
    moccasin: [255, 228, 181],
    peach_puff: [255, 218, 185],
    pale_goldenrod: [238, 232, 170],
    khaki: [240, 230, 140],
    dark_khaki: [189, 183, 107],
    lavender: [230, 230, 250],
    thistle: [216, 191, 216],
    plum: [221, 160, 221],
    violet: [238, 130, 238],
    orchid: [218, 112, 214],
    fuchsia: [255, 0, 255],
    magenta: [255, 0, 255],
    medium_orchid: [186, 85, 211],
    medium_purple: [147, 112, 219],
    blue_violet: [138, 43, 226],
    dark_violet: [148, 0, 211],
    dark_orchid: [153, 50, 204],
    dark_magenta: [139, 0, 139],
    purple: [128, 0, 128],
    indigo: [75, 0, 130],
    dark_slate_blue: [72, 61, 139],
    slate_blue: [106, 90, 205],
    medium_slate_blue: [123, 104, 238],
    green_yellow: [173, 255, 47],
    chartreuse: [127, 255, 0],
    lawn_green: [124, 252, 0],
    lime: [0, 255, 0],
    lime_green: [50, 205, 50],
    pale_green: [152, 251, 152],
    light_green: [144, 238, 144],
    medium_spring_green: [0, 250, 154],
    spring_green: [0, 255, 127],
    medium_sea_green: [60, 179, 113],
    sea_green: [46, 139, 87],
    forest_green: [34, 139, 34],
    green: [0, 128, 0],
    dark_green: [0, 100, 0],
    yellow_green: [154, 205, 50],
    olive_drab: [107, 142, 35],
    olive: [128, 128, 0],
    dark_olive_green: [85, 107, 47],
    medium_aquamarine: [102, 205, 170],
    dark_sea_green: [143, 188, 143],
    light_sea_green: [32, 178, 170],
    dark_cyan: [0, 139, 139],
    teal: [0, 128, 128],
    aqua: [0, 255, 255],
    cyan: [0, 255, 255],
    light_cyan: [224, 255, 255],
    pale_turquoise: [175, 238, 238],
    aquamarine: [127, 255, 212],
    turquoise: [64, 224, 208],
    medium_turquoise: [72, 209, 204],
    dark_turquoise: [0, 206, 209],
    cadet_blue: [95, 158, 160],
    steel_blue: [70, 130, 180],
    light_steel_blue: [176, 196, 222],
    powder_blue: [176, 224, 230],
    light_blue: [173, 216, 230],
    sky_blue: [135, 206, 235],
    light_sky_blue: [135, 206, 250],
    deep_sky_blue: [0, 191, 255],
    dodger_blue: [30, 144, 255],
    cornflower_blue: [100, 149, 237],
    royal_blue: [65, 105, 225],
    blue: [0, 0, 255],
    medium_blue: [0, 0, 205],
    dark_blue: [0, 0, 139],
    navy: [0, 0, 128],
    midnight_blue: [25, 25, 112],
    cornsilk: [255, 248, 220],
    blanched_almond: [255, 235, 205],
    bisque: [255, 228, 196],
    navajo_white: [255, 222, 173],
    wheat: [245, 222, 179],
    burly_wood: [222, 184, 135],
    tan: [210, 180, 140],
    rosy_brown: [188, 143, 143],
    sandy_brown: [244, 164, 96],
    goldenrod: [218, 165, 32],
    dark_goldenrod: [184, 134, 11],
    peru: [205, 133, 63],
    chocolate: [210, 105, 30],
    saddle_brown: [139, 69, 19],
    sienna: [160, 82, 45],
    brown: [165, 42, 42],
    maroon: [128, 0, 0],
    white: [255, 255, 255],
    snow: [255, 250, 250],
    honeydew: [240, 255, 240],
    mint_cream: [245, 255, 250],
    azure: [240, 255, 255],
    alice_blue: [240, 248, 255],
    ghost_white: [248, 248, 255],
    white_smoke: [245, 245, 245],
    seashell: [255, 245, 238],
    beige: [245, 245, 220],
    old_lace: [253, 245, 230],
    floral_white: [255, 250, 240],
    ivory: [255, 255, 240],
    antique_white: [250, 235, 215],
    linen: [250, 240, 230],
    lavender_blush: [255, 240, 245],
    misty_rose: [255, 228, 225],
    gainsboro: [220, 220, 220],
    light_grey: [211, 211, 211],
    silver: [192, 192, 192],
    dark_gray: [169, 169, 169],
    gray: [128, 128, 128],
    dim_gray: [105, 105, 105],
    light_slate_gray: [119, 136, 153],
    slate_gray: [112, 128, 144],
    dark_slate_gray: [47, 79, 79],
    black: [0, 0, 0]
  }.freeze

  COLOR_NAMES = COLORS.keys.freeze

  # Create a new Color object. 
  # 
  # @param name [String] the name of the color
  # @param a [Numeric] the amount of alpha, 0..255
  # 
  # @return [Color::NamedColor] a new Color::NamedColor instance
  def initialize(name="Black", a=255)
    name = name.to_s
    if ! COLOR_NAMES.include? name
      raise "Color name could not be found!: #{name}"
    end
    @name = name
    @a = a
  end

  # Returns the name and opacity in a hash.
  # 
  # @return [Hash]
  def to_hash
    {name: @name, a: @a}
  end

  # Returns a Color::Rgb instance to closely match the named color.
  # 
  # @return [Color::Rgb]
  def to_rgb
    r, g, b = COLORS[name]
    Color::Rgb.new(r, g, b, @a)
  end

  def to_hsv
      to_rgb.to_hsv
  end
end
