import bpy

for collection in bpy.data.collections:
    for object in collection.objects:
        object.hide_render = True

for collection in bpy.data.collections:
    for object in collection.objects:
        object.hide_render = False
        bpy.context.scene.render.filepath = "/tmp/"+object.name
        bpy.ops.render.render(write_still = True)
        object.hide_render = True
        
for collection in bpy.data.collections:
    for object in collection.objects:
        object.hide_render = False