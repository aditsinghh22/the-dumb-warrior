
from flask import Flask, request, jsonify, render_template


app = Flask(__name__)


story_data = {
    'start': {
        'text':
        "Narrator: In a kingdom where dental insurance was a distant dream, a hero was needed. Behold, Leo! He stood mesmerized before a bounty poster. 'SLAY THE DRAGON, GET 10,000 GOLD,' it read.\n\nLeo: Hey, Narrator! Just so we're clear, this pan isn't just for cooking. It's a... dragon-bonking instrument.\n\nNarrator: Whatever helps you sleep at night, kid. Before you, the path splits. To the left, a path shrouded in shadow. To his right, a path bathed in cheerful sunlight.",
        'choices': [{
            'id': 0,
            'text': "Take the dark, horror path.",
            'next_scene': 'scene_adventurers'
        }, {
            'id': 1,
            'text': "Take the path with full daylight.",
            'next_scene': 'scene_sunny_path'
        }]
    },
    'scene_sunny_path': {
        'text':
        "Narrator: Leo, deciding that skulls were bad for his complexion, wisely chose the sunny path. He frolicked through a meadow of beautiful, yellow Buttercups.\n\nLeo: See? This is much better! What could possibly go wrong?\n\nNarrator: What could go wrong, indeed. It turns out that Buttercups, while cheerful, are also incredibly poisonous to ingest. And in his frolicking, Leo had tripped and face-planted...",
        'choices': [{
            'id': 0,
            'text': "(Continue...)",
            'next_scene': 'ending_coward'
        }]
    },
    'scene_adventurers': {
        'text':
        "Narrator: Leo, filled with a courage he definitely didn't feel, plunged into the darkness. After an hour of fumbling, he stumbled into a clearing with a warm campfire. Three grizzled adventurers sharpening actual swords looked at Leo, then at his frying pan, and sighed.\n\nAdventurer: ...You lost, kid?",
        'choices': [{
            'id': 0,
            'text': "Fight them! Their gear looks expensive.",
            'next_scene': 'ending_skill_issue'
        }, {
            'id': 1,
            'text': "Leave them alone. They look scary.",
            'action': 'set_inventory',
            'item': 'Fire Rune',
            'next_scene': 'adventurers_get_rune'
        }, {
            'id': 2,
            'text': "Ask to join their team.",
            'action': 'set_inventory',
            'item': 'Scrap Metal',
            'next_scene': 'adventurers_get_scrap'
        }]
    },
    'adventurers_get_rune': {
        'text':
        "Narrator: Leo wisely decided not to antagonize the people holding pointy objects. As he backed away, the leader chuckled.\n\nAdventurer: Wait, kid. It's dangerous out here. Take this.\n\nNarrator: She tossed him a small, red stone that pulsed with a warm light.\n\n** You got a FIRE RUNE! **",
        'choices': [{
            'id': 0,
            'text': "Press on towards the lair.",
            'next_scene': 'scene_dragon_lair'
        }]
    },
    'adventurers_get_scrap': {
        'text':
        "Narrator: The adventurers looked at his pan. Then at each other. Then they burst out laughing.\n\nAdventurer: Hah! No. We don't have a \"culinary division.\" But hey, for trying, you can have this.\n\nNarrator: One of them tossed him a bent piece of metal.\n\n** You got some SCRAP METAL! **",
        'choices': [{
            'id': 0,
            'text': "Press on towards the lair.",
            'next_scene': 'scene_dragon_lair'
        }]
    },
    'scene_dragon_lair': {
        'text':
        "Narrator: Whether he was equipped with a magical rune or a piece of junk, Leo pressed on. Finally, he reached the entrance to the dragon's lair. Inside, sleeping atop a mountain of gold, was a colossal red dragon.\n\nLeo: (Whispering) Okay, Narrator. No more tricks. What's the plan?",
        'choices': [{
            'id': 0,
            'text': "Charge! For glory and gold!",
            'next_scene': 'ending_cremation'
        }, {
            'id': 1,
            'text': "Try to create a diversion.",
            'next_scene': 'check_inventory_ending'
        }]
    },
    'check_inventory_ending': {
        'text': "Leo decides to create a diversion...",
        'logic': 'check_inventory'
    },
    'ending_coward': {
        'title': 'ENDING 1: A COWARD\'S END',
        'text':
        "Narrator: He lay there, paralyzed, as a herd of fluffy sheep trotted over and began to nibble on his hair. A truly pathetic sight.\n\n(You died from a botanical blunder. Maybe the scary path was safer.)",
        'is_ending': True
    },
    'ending_skill_issue': {
        'title': 'ENDING 2: SKILL ISSUE',
        'text':
        "Narrator: The adventurers didn't even stand up. Their leader, a woman with a scar over one eye, flicked a pebble at Leo's forehead. He crumpled to the ground, unconscious. They took his pan.\n\n(You were defeated by a pebble. A PEBBLE. Let that sink in.)",
        'is_ending': True
    },
    'ending_cremation': {
        'title': 'ENDING 3: UNSCHEDULED CREMATION',
        'text':
        "Leo: Wait, maybe this wasn't such a good—\n\nNarrator: It was not, in fact, a good idea. A torrent of fire erupted from the dragon's maw, engulfing our hero. He was simply... gone. A puff of smoke and a faint, lingering smell of burnt toast.",
        'is_ending': True
    },
    'ending_accidental_hero_rune': {
        'title': 'WINNER: THE ACCIDENTAL HERO',
        'text':
        "Narrator: Leo slapped the fire rune onto his pan. It immediately began to glow cherry-red. He hurled it at a far wall, causing a massive, deafening BOOM! The startled dragon fled out a back exit in a panic. The treasure was all his.\n\n(You somehow succeeded. You're rich! Now you can finally afford a real weapon.)",
        'is_ending': True
    },
    'ending_accidental_hero_scrap': {
        'title': 'WINNER: THE ACCIDENTAL HERO',
        'text':
        "Narrator: Leo hurled the scrap metal. It ricocheted and embedded itself in the dragon's nostril. The dragon awoke with a titanic sneeze that blew Leo—and half the treasure—out of the cave. It then flew away, trying to dislodge the metal from its nose.\n\n(You somehow succeeded. You're rich! Now you can finally afford a real weapon.)",
        'is_ending': True
    }
}

game_state = {'current_scene': 'start', 'inventory': 'Nothing'}

@app.route("/")
def serve_index():
    return render_template('index.html')


@app.route("/game_state")
def get_game_state():
    current_scene_data = story_data[game_state['current_scene']]
    return jsonify({
        'scene': current_scene_data,
        'inventory': game_state['inventory']
    })


@app.route("/choose", methods=['POST'])
def choose():
    choice_id = request.json['choice_id']
    current_scene = story_data[game_state['current_scene']]
    choice = current_scene['choices'][choice_id]

    if 'action' in choice and choice['action'] == 'set_inventory':
        game_state['inventory'] = choice['item']

    next_scene_key = choice['next_scene']

    if next_scene_key == 'check_inventory_ending':
        if game_state['inventory'] == 'Fire Rune':
            next_scene_key = 'ending_accidental_hero_rune'
        else:
            next_scene_key = 'ending_accidental_hero_scrap'

    game_state['current_scene'] = next_scene_key
    return get_game_state()


@app.route("/restart", methods=['POST'])
def restart():
    game_state['current_scene'] = 'start'
    game_state['inventory'] = 'Nothing'
    return get_game_state()


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=81)
