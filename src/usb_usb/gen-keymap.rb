
class Regexp
  def full_match(str)
    m = self.match(str)
    m and m[0] == str
  end
end

class Keymap
  def initialize(keymap, keys = nil)
    if keys
      @type, @keys = keymap, keys
    elsif keymap =~ /(KEYMAP\w*)\s*\((.*)\)/m
      @type, keys = $1, $2.strip.split(/\n/)
      @keys = keys.map{ |ks| ks.strip.split(/\s*,\s*/) }
    else
      fail keymap
    end
  end
  def keys ; @keys end

  def map_key(kmap, &code)
    keep_keys  = kmap[:keep_keys]
    match_kept_keys = proc do |key|
      if ((keep_keys.kind_of?(Regexp) and keep_keys.full_match(key)) or
          (keep_keys.kind_of?(Array)  and keep_keys.include? key) or
          (keep_keys.kind_of?(String) and keep_keys == key ))
        key
      else
        nil
      end
    end
    trans_keys = kmap[:trans_keys]
    match_trans_keys = proc do |key|
      rule, new_key = *trans_keys
      if rule.kind_of? Regexp and new_key and rule.full_match(key)
        new_key
      else
        nil
      end
    end
    key_for_others = kmap[:others]

    keys = @keys.map do |ks|
      ks.map do |key|
        (kmap[key] || kmap[key.to_sym] ||
         (code && code.call(key)) ||
         match_kept_keys.call(key) ||
         match_trans_keys.call(key) ||
         key_for_others ||
         key)
      end
    end
    Keymap.new @type, keys
  end
  def merge(kmap_b)
    keys = @keys.map.with_index do |ks, ks_i|
      ks_b = kmap_b.keys[ks_i]
      ks.map.with_index do |k_a, k_i|
        k_b = ks_b[k_i]
        (k_a == "TRNS" or
         k_a == "NO" and k_b != "TRNS") ? k_b : k_a
      end
    end
    Keymap.new @type, keys
  end

  def to_code
    @type + '(' + @keys.flatten.join(', ') + ')'
  end
  def dump
    puts @type + '('
    @keys.each do |ks|
      puts "    " + ks.map{ |k| "%5s" % k }.join(', ')
    end
    puts ')'
  end
end

if __FILE__ == $0
  k87 = "
  KEYMAP_K87(
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
    FN5, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          FN6,
    LCTL,LGUI,LALT,          FN1,                     FN0, RALT,RGUI,RCTL,
  )"
  k60 = "
  KEYMAP_K60( ESC, 
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, 
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, 
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT, 
    LCTL,LGUI,LALT,               SPC,                RALT,RGUI,APP, RCTL  
  )"
  keymap = Keymap.new(k60)
  keymap_1 = keymap.map_key({ 'I' => 'UP', 'K' => 'DOWN' })
  puts keymap_1.to_code
  keymap_1.dump
  keymap.map_key({ J: 'LEFT', K: 'DOWN', L: 'RGHT', keep_keys: /[LR](CTL|GUI|ALT)/,
                   trans_keys: [ /[QWERASDFZXCV]/, 'NO' ], others: 'TRNS' }
                 ).dump
  keymap.map_key({ J: 'LEFT', K: 'DOWN', L: 'RGHT', keep_keys: /[LR](CTL|GUI|ALT)/,
                   trans_keys: [ /[QWERASDFZXCV]/, 'NO' ], others: 'TRNS' }) do |key|
    key == 'APP' ? key : nil
  end.dump
end
