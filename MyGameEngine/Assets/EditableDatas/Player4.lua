Object3D = {
    name = "BadGuy",
    initial_position = { 180, -500, 0},
    initial_rotation = { 0, 0, 0},

    Physics2D_settings = {
        mass = 2.0,
        air_friction = 0,
        velocity = {0, 0.2, 0},
        accelaration = {0, 0, 0}
    },

    SpriteRender_settings = {
        path = "..\\Assets\\data\\BadGuy.dds"
    },
}