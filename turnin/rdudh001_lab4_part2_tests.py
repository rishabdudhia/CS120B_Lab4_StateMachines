# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ 
    {'description': 'PINA: 0x01, 0x07, 0x00, 0x89, 0x6F, 0x03, 0x85 => PORTC: 0x09',
    'steps':[{'inputs':[('PINA', 0x01)], 'iterations': 2},
	{'inputs': [('PINA', 0x07)], 'iterations': 100 },
	{'inputs': [('PINA', 0x00)], 'iterations': 100 },
	{'inputs': [('PINA', 0x89)],'iterations': 100 },
	{'inputs': [('PINA', 0x6F)], 'iterations': 100 },
	{'inputs': [('PINA',0x03)], 'iterations': 50 },
	{'inputs': [('PINA',0x85)], 'iterations':50}],
    'expected': [('PORTC',0x09)],
    },
    {'description': 'PINA: 0x02, 0x00, 0x02 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 100 },
	{'inputs': [('PINA',0x02)], 'iterations': 100 },
	{'inputs': [('PINA', 0x00)], 'iterations':100},
	{'inputs': [('PINA', 0x02)], 'iterations': 100} ],
    'expected': [('PORTC',0x00)],
    },
    {'description': 'PINA: 0x00 => PORTC: 0x00',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 2 },
        {'inputs': [('PINA',0x00)], 'iterations': 100 },
        {'inputs': [('PINA', 0x00)], 'iterations': 2},
        {'inputs': [('PINA', 0x00)], 'iterations': 2} ],
    'expected': [('PORTC',0x00)],
    },
    {'description': 'PINA: 0x01 => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
        {'inputs': [('PINA',0x01)], 'iterations': 100 },
        {'inputs': [('PINA', 0x01)], 'iterations': 2},
        {'inputs': [('PINA', 0x01)], 'iterations': 2} ],
    'expected': [('PORTC',0x01)],
    },
    {'description': 'PINA: 0x01, 0x00, 0x01 0x00 , 0x01 => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
        {'inputs': [('PINA',0x00)], 'iterations': 100 },
        {'inputs': [('PINA', 0x01)], 'iterations': 2},
        {'inputs': [('PINA', 0x00)], 'iterations': 2},
	{'inputs': [('PINA', 0x01)], 'iterations': 50} ],
    'expected': [('PORTC',0x01)],
    },
    {'description': 'PINA: 0x01, PINA: 0xFF => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
        {'inputs': [('PINA',0xFF)], 'iterations': 100 }],
    'expected': [('PORTC',0x01)],
    },
    {'description': 'PINA: 0x01, 0xC1, 0x00, 0x04 , 0x05 => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
        {'inputs': [('PINA',0xC1)], 'iterations': 100 },
        {'inputs': [('PINA', 0x00)], 'iterations': 2},
        {'inputs': [('PINA', 0x04)], 'iterations': 2},
        {'inputs': [('PINA', 0x05)], 'iterations': 50} ],
    'expected': [('PORTC',0x01)],
    },
    {'description': 'PINA: 0x07, 0x09, 0x01 0xA3 , 0x71 => PORTC: 0x03',
    'steps': [ {'inputs': [('PINA',0x07)], 'iterations': 2 },
        {'inputs': [('PINA',0x09)], 'iterations': 100 },
        {'inputs': [('PINA', 0x01)], 'iterations': 2},
        {'inputs': [('PINA', 0xA3)], 'iterations': 2},
        {'inputs': [('PINA', 0x71)], 'iterations': 50} ],
    'expected': [('PORTC',0x03)],
    },
    {'description': 'PINA: 0x06, PINA: 0x2 => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x06)], 'iterations': 2 },
        {'inputs': [('PINA',0x02)], 'iterations': 100 }],
    'expected': [('PORTC',0x02)],
    },
    {'description': 'PINA: 0x21, 0x33, 0x00, 0xFF , 0x05 => PORTC: 0x04',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
        {'inputs': [('PINA',0xC1)], 'iterations': 100 },
        {'inputs': [('PINA', 0x00)], 'iterations': 2},
        {'inputs': [('PINA', 0x04)], 'iterations': 2},
        {'inputs': [('PINA', 0x05)], 'iterations': 50} ],
    'expected': [('PORTC',0x01)],
    },
    ]

# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
watch = ['state','cntA0', 'cntA1','Tick::actualC']

