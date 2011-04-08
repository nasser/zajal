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
    
    Events::Internals.update_prehooks.push cleanup_video_ary_hook
    Events::Internals.update_prehooks.push update_videos_hook
    
    
    # stop playing videos that weren't drawn
    autostop_videos_prehook = proc {
      video_hash.values.each do |vid|
        vid.was_drawn = false
      end
    }
    
    # stop playing videos that weren't drawn
    autostop_videos_posthook = proc {
      video_hash.values.each do |vid|
        unless vid.was_drawn
          vid.pause
        end
      end
    }
    
    Events::Internals.draw_prehooks.push autostop_videos_prehook
    Events::Internals.draw_posthooks.push autostop_videos_posthook
    
  end
end