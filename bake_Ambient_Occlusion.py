import bpy

object = bpy.context.active_object

size = 2048
sample = 32
distance = 0.5
filePath = "/tmp/"

aoImage = bpy.data.images.new("aoImage", width=size, height=size)
normalImage = bpy.data.images.new("normalImage", width=size, height=size)

oldSample = bpy.context.scene.cycles.samples
oldREngine = bpy.context.scene.render.engine
oldAS = bpy.context.scene.cycles.use_adaptive_sampling
oldD = bpy.context.scene.world.light_settings.distance

bpy.context.scene.world.light_settings.distance = 0.5
bpy.context.scene.render.engine = 'CYCLES'
bpy.context.scene.cycles.samples = sample
bpy.context.scene.cycles.use_adaptive_sampling = True

if len(bpy.context.object.material_slots) == 0:
    material = bpy.data.materials.new("aoMaterial")
    object.data.materials.append(material)

    material.use_nodes = True
    nodes = material.node_tree.nodes

    imageNode = nodes.new('ShaderNodeTexImage')
    imageNode.image = aoImage
    nodes.active = imageNode

    bpy.ops.object.bake(type='AO', save_mode='EXTERNAL', margin=16)

    bpy.context.scene.cycles.samples = 1
    imageNode.image = normalImage
    bpy.ops.object.bake(type='NORMAL', save_mode='EXTERNAL',
                        margin=16, normal_space='OBJECT')

    bpy.ops.object.material_slot_remove()
    bpy.data.materials.remove(material)
else:
    material = bpy.context.object.active_material
    material.use_nodes = True

    nodes = material.node_tree.nodes

    imageNode = nodes.new('ShaderNodeTexImage')
    imageNode.image = aoImage
    nodes.active = imageNode

    bpy.ops.object.bake(type='AO', save_mode='EXTERNAL', margin=16)

    bpy.context.scene.cycles.samples = 1
    imageNode.image = normalImage
    bpy.ops.object.bake(type='NORMAL', save_mode='EXTERNAL',
                        margin=16, normal_space='OBJECT')
    nodes.remove(imageNode)

bpy.context.scene.cycles.samples = oldSample
bpy.context.scene.render.engine = oldREngine
bpy.context.scene.cycles.use_adaptive_sampling = oldAS
bpy.context.scene.world.light_settings.distance = oldD
# composite
scene = bpy.data.scenes.new("bakeScene")

scene.use_nodes = True
nodetree = scene.node_tree

for a in nodetree.nodes:
    nodetree.nodes.remove(a)

nDenoise = nodetree.nodes.new("CompositorNodeDenoise")
nAoImage = nodetree.nodes.new("CompositorNodeImage")
nNormalImage = nodetree.nodes.new("CompositorNodeImage")
nComposite = nodetree.nodes.new("CompositorNodeComposite")

nAoImage.image = aoImage
nNormalImage.image = normalImage

nodetree.links.new(nAoImage.outputs[0], nDenoise.inputs[0])
nodetree.links.new(nNormalImage.outputs[0], nDenoise.inputs[1])
nodetree.links.new(nDenoise.outputs[0], nComposite.inputs[0])

scene.render.filepath = filePath+object.name+"_ao"
scene.render.resolution_x = size
scene.render.resolution_y = size

bpy.ops.render.render(write_still=True, scene=scene.name)
bpy.data.scenes.remove(scene)

bpy.data.images.remove(aoImage)
bpy.data.images.remove(normalImage)
