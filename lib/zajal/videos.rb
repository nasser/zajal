module Videos
  module Internals
    # remove ids of recycled videos from video_ary
    cleanup_video_ary_hook = proc {
      video_ary.reject! do |vid_id|
        begin
          vid_id.to_ref
          false
        rescue RangeError
          true
        end
      end
    }
    
    # update all active videos
    update_videos_hook = proc {
      video_ary.each do |vid_id|
        vid_id.to_ref.update
      end
    }
    
    Events::Internals.update_hooks.push cleanup_video_ary_hook
    Events::Internals.update_hooks.push update_videos_hook
  end
end